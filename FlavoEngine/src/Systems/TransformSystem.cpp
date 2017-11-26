#include "Systems/TransformSystem.h"
#include "Transform.h"
#include "SceneObject.h"
#include <glm/gtc/matrix_transform.hpp>

Engine::TransformSystem::TransformSystem() {

}

Engine::TransformSystem::~TransformSystem() {

}

void Engine::TransformSystem::Update(EntityManager& es, EventManager& events, TimeDelta dt) {
	ComponentHandle<Transform> transformHandle;
	for (Entity entity : es.entities_with_components(transformHandle)) {
		if (!transformHandle.IsValid()) { continue; }

		Transform* trans = transformHandle.Get();
		if (!trans->bHasParentChanged) { continue; }

		if (trans->Parent.IsDefault()) {
			RootTransforms.insert(std::pair<Entity, ComponentHandle<Transform>>(entity, transformHandle));
		} else {
			auto it = RootTransforms.find(entity);
			if (it != RootTransforms.end()) {
				RootTransforms.erase(entity);
			}
		}
	}

	for (std::pair<Entity, ComponentHandle<Transform>> pair : RootTransforms) {
		ChangeWorld(pair.second, false);
	}
}

void Engine::TransformSystem::ChangeWorld(ComponentHandle<Transform> TransHandle, bool bIsParentDirty) {
	static glm::vec3 up(0.0f, 1.0f, 0.0f);
	static glm::vec3 forward(0.0f, 0.0f, 1.0f);
	static glm::vec3 right(-1.0f, 0.0f, 0.0f);

	if (!TransHandle.IsValid())
		return;

	Transform* trans = TransHandle.Get();

	if (trans->Dirtiness == TransformDirtiness::PendingApply) {
		glm::mat4 local = glm::mat4(1.0f);
		glm::mat4 scaleMat = glm::scale(local, trans->LocalScale);
		glm::mat4 rotMat = (glm::mat4)trans->LocalRotation;
		glm::mat4 posMat = glm::translate(local, trans->LocalPosition);

		trans->LocalWorld = posMat * rotMat * scaleMat;
		if (!trans->Parent.IsDefault() && trans->Parent.IsValid())
			trans->World = trans->LocalWorld * trans->Parent.Get()->World;
		else
			trans->World = trans->LocalWorld;
		trans->Dirtiness = TransformDirtiness::AppliedTransform;
	} else {
		if (bIsParentDirty && trans->Parent.IsValid()) {
			trans->World = trans->Parent.Get()->World * trans->LocalWorld;
		}
	}

	trans->Forward = glm::vec3(trans->World[2]);
	trans->Up = glm::vec3(trans->World[1]);
	trans->Right = -glm::vec3(trans->World[0]);
	trans->Position = glm::vec3(trans->World[3]);

	for (auto it : trans->Children) {
		if (!it.second.IsValid())
			continue;
		ChangeWorld(it.second, (trans->Dirtiness != TransformDirtiness::NoChange) || bIsParentDirty);
	}
}
