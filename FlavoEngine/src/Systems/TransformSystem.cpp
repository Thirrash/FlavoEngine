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
	if (!TransHandle.IsValid())
		return;

	Transform* trans = TransHandle.Get();
	if (trans->bIsDirty) {
		glm::mat4 local = glm::mat4(1.0f);
		glm::mat4 scaleMat = glm::scale(local, trans->LocalScale);
		glm::mat4 rotMat = (glm::mat4)trans->LocalRotation;
		glm::mat4 posMat = glm::translate(local, trans->LocalPosition);

		trans->LocalWorld = posMat * rotMat * scaleMat;
		if (!trans->Parent.IsDefault() && trans->Parent.IsValid())
			trans->World = trans->Parent.Get()->World * trans->LocalWorld;
		else
			trans->World = trans->LocalWorld;
	} else {
		if (bIsParentDirty && trans->Parent.IsValid()) {
			trans->World = trans->Parent.Get()->World * trans->LocalWorld;
		}
	}

	//temporary
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	glm::vec3 forward(0.0f, 0.0f, 1.0f);
	glm::vec3 right(-1.0f, 0.0f, 0.0f);
	trans->Forward = glm::vec3(trans->World[2]);
	trans->Up = glm::vec3(trans->World[1]);
	trans->Right = -glm::vec3(trans->World[0]);

	//glm::vec3 forward = glm::vec3(0.0f);
	//forward.x = cos(glm::radians(trans->Rotation.x) * cos(glm::radians(trans->Rotation.y)));
	//forward.y = sin(glm::radians(trans->Rotation.x));
	//forward.z = cos(glm::radians(trans->Rotation.x) * sin(glm::radians(trans->Rotation.y)));
	//forward = glm::normalize(forward);

	//trans->Forward = forward;
	//trans->Right = glm::cross(forward, up);
	//trans->Up = -glm::cross(forward, trans->Right);

	for (auto it : trans->Children) {
		if (!it.second.IsValid())
			continue;
		ChangeWorld(it.second, trans->bIsDirty || bIsParentDirty);
	}
}
