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

		local = glm::scale(local, glm::vec3(trans->LocalScale.X, trans->LocalScale.Y, trans->LocalScale.Z));
		local = glm::rotate(local, (float)trans->LocalRotation.X, glm::vec3(1.0f, 0.0f, 0.0f));
		local = glm::rotate(local, (float)trans->LocalRotation.Y, glm::vec3(0.0f, 1.0f, 0.0f));
		local = glm::rotate(local, (float)trans->LocalRotation.Z, glm::vec3(0.0f, 0.0f, 1.0f));
		local = glm::translate(local, glm::vec3(trans->LocalPosition.X, trans->LocalPosition.Y, trans->LocalPosition.Z));

		trans->LocalWorld = local;
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
	glm::vec3 forward = glm::vec3(0.0f);
	forward.x = cos(glm::radians(trans->Rotation.X)) * cos(glm::radians(trans->Rotation.Y));
	forward.y = sin(glm::radians(trans->Rotation.X));
	forward.z = cos(glm::radians(trans->Rotation.X)) * sin(glm::radians(trans->Rotation.Y));
	forward = glm::normalize(forward);
	trans->Forward = Vector3(forward.x, forward.y, forward.z);
	glm::vec3 right = glm::cross(forward, up);
	trans->Right = Vector3(right.x, right.y, right.z);

	for (auto it : trans->Children) {
		if (!it.second.IsValid())
			continue;
		ChangeWorld(it.second, trans->bIsDirty || bIsParentDirty);
	}
}
