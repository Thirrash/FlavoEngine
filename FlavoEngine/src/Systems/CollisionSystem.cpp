#include "Systems/CollisionSystem.h"
#include "Collider.h"
#include "Transform.h"
#include "Debug.h"
#include "SceneObject.h"
#include <set>
#include <math.h>

float Engine::CollisionSystem::CellSize = 20.0f;
std::unordered_map<glm::vec3, std::set<Engine::ComponentHandle<Engine::Collider>>, Engine::CollisionSystem::Vec3Hasher> Engine::CollisionSystem::CollidingMap;

Engine::CollisionSystem::CollisionSystem() {

}

Engine::CollisionSystem::~CollisionSystem() {

}

bool Engine::CollisionSystem::Raycast(const glm::vec3& Origin, const glm::vec3& End, ComponentHandle<Collider>& HitCollider, glm::vec3& HitPoint) {
	const int noHops = 100;
	const float deltaT = 1.0f / (float)noHops;
	const glm::vec3& dir = End - Origin;

	std::set<glm::vec3, GlmVec3Comparer> bounds;
	glm::vec3 tmp = Origin;
	for (int i = 0; i < noHops; i++) {
		tmp = Origin + (float)i * deltaT * dir;
		float x = std::floor(tmp.x / CellSize), y = std::floor(tmp.y / CellSize), z = std::floor(tmp.z / CellSize);
		bounds.insert(glm::vec3(CellSize * x, CellSize * y, CellSize * z));
	}

	auto colComp = [](const ComponentHandle<Collider>& First, const ComponentHandle<Collider>& Second) {
		return First.Get()->AssignedTo->Id < Second.Get()->AssignedTo->Id;
	};

	std::set<ComponentHandle<Collider>, decltype(colComp)> cols(colComp);
	for (auto it : bounds) {
		for (auto itc : CollidingMap[it]) {
			cols.insert(itc);
		}
		//LogB((it).x, (it).y, (it).z, cols.size(), CollidingMap[it].size());
	}

	for (auto it : cols) {
		//LogD(it.Get()->AssignedTo->Name);
		if (it.Get()->CheckLineCollision(Origin, End, it.Get()->AssignedTo->Get<Transform>().Get(), HitPoint)) {
			HitCollider = it;
			return true;
		}
	}

	return false;
}

void Engine::CollisionSystem::Update(EntityManager& es, EventManager& events, TimeDelta dt) {
	ComponentHandle<Collider> colliderHandle;
	ComponentHandle<Transform> transformHandle;
	for (Entity entity : es.entities_with_components(transformHandle, colliderHandle)) {
		if (!transformHandle.IsValid() || !colliderHandle.IsValid()) {
			LogW("Handle not valid for: ", entity.id().id());
			continue;
		}

		UpdateCollidingMap(colliderHandle, transformHandle);
	}
}

void Engine::CollisionSystem::UpdateCollidingMap(ComponentHandle<Collider>& ColliderHandle, ComponentHandle<Transform>& TransformHandle) {
	Transform* transform = TransformHandle.Get();
	Collider* collider = ColliderHandle.Get();
	if (transform->Dirtiness != TransformDirtiness::AppliedTransform && !collider->bIsDirty) {
		return;
	}

	collider->WorldBoundingBox[0] = collider->LocalBoundingBox[0] + glm::vec2(transform->Position.x, transform->Position.x);
	collider->WorldBoundingBox[1] = collider->LocalBoundingBox[1] + glm::vec2(transform->Position.y, transform->Position.y);
	collider->WorldBoundingBox[2] = collider->LocalBoundingBox[2] + glm::vec2(transform->Position.z, transform->Position.z);
	//LogB(collider->WorldBoundingBox[0].x, collider->WorldBoundingBox[1].x, collider->WorldBoundingBox[2].x);

	std::vector<float>* cells = new std::vector<float>[3];
	for (int i = 0; i < 3; i++) {
		float val = std::floor(collider->WorldBoundingBox[i].x / CellSize);
		cells[i].push_back(val);
		//LogD(collider->AssignedTo->Id.id().id(), i, cells[i].back(), collider->WorldBoundingBox[i].x);
		while ((float)(cells[i].back() + 1.0f) * (CellSize) < collider->WorldBoundingBox[i].y) {
			cells[i].push_back(cells[i].back() + 1.0f);
			//LogD(collider->AssignedTo->Id.id().id(), i, cells[i].back());
		}
	}

	std::set<glm::vec3, GlmVec3Comparer> cellEraseSet(collider->CurrentCells);
	for (float x = cells[0].front(); x <= cells[0].back(); x++) {
		for (float y = cells[1].front(); y <= cells[1].back(); y++) {
			for (float z = cells[2].front(); z <= cells[2].back(); z++) {
				glm::vec3 key(x * CellSize, y * CellSize, z * CellSize);
				auto it = CollidingMap.find(key);
				if (it == CollidingMap.end()) {
					CollidingMap.insert({ key, std::set<ComponentHandle<Collider>>() });
				}

				std::set<glm::vec3>::iterator cellIt = cellEraseSet.find(key);
				if (cellIt != cellEraseSet.end()) {
					cellEraseSet.erase(cellIt);
				} else {
					//LogB("Before:", CollidingMap[key].size(), key.x, key.y, key.z, collider->AssignedTo->Name);
					//if (CollidingMap[key].size() != 0)
					//	LogC(CollidingMap[key].begin()->id_.id(), ColliderHandle.id_.id());
					CollidingMap[key].insert(ColliderHandle);
					collider->CurrentCells.insert(key);
					//LogB("After:", CollidingMap[key].size(), key.x, key.y, key.z, collider->AssignedTo->Name);
					//LogA("Insert", collider->AssignedTo->Name, key.x, key.y, key.z);
				}
			}
		}
	}

	for (auto it : cellEraseSet) {
		collider->CurrentCells.erase(it);
	}

	collider->bIsDirty = false;
	delete[] cells;
}
