#include "SceneObjectHandle.h"
#include "SceneObject.h"

Engine::SceneObjectHandle::SceneObjectHandle() : Manager(nullptr), Object(nullptr) {
	Id = Entity();
}

Engine::SceneObjectHandle::SceneObjectHandle(EntityManager* Manager, SceneObject* Object) : Manager(Manager), Object(Object) {
	Id = Object->Id;
}

Engine::SceneObjectHandle::~SceneObjectHandle() {

}

Engine::SceneObject* Engine::SceneObjectHandle::Get() {
	if (!IsValid()) {
		return nullptr;
	}

	return Object;
}

bool Engine::SceneObjectHandle::IsValid() {
	if (Manager == nullptr)
		return false;

	return Manager->valid(Id.id());
}

void Engine::SceneObjectHandle::Destroy() {
	if (!IsValid()) {
		return;
	}

	delete Object;
}