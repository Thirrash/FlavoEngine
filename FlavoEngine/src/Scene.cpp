#include "Scene.h"
#include "SceneObject.h"
#include "Transform.h"

Engine::Scene::Scene() {
	SceneObject* cameraObj = new SceneObject(entities.create());
	MainCamera = SceneObjectHandle(&entities, cameraObj);
	Objects.insert(std::pair<Entity::Id, SceneObjectHandle>(cameraObj->Id.id(), MainCamera));
}

Engine::Scene::~Scene() {

}

Engine::SceneObjectHandle Engine::Scene::Instantiate() {
	SceneObject* newObj = new SceneObject(entities.create());
	SceneObjectHandle handle(&entities, newObj);
	Objects.insert(std::pair<Entity::Id, SceneObjectHandle>(newObj->Id.id(), handle));

	return handle;
}

bool Engine::Scene::Destroy(Engine::SceneObjectHandle Object) {
	if (!Object.IsValid()) {
		return false;
	}

	auto it = Objects.find(Object.Get()->Id.id());
	if (it == Objects.end()) {
		return false;
	}

	Object.Destroy();
	Objects.erase(it);
}

Engine::EventManager& Engine::Scene::GetEventManager() {
	return events;
}

void Engine::Scene::ChangeParent(ComponentHandle<Transform> Parent, ComponentHandle<Transform> Child) {
	if (!Parent.IsValid() || !Child.IsValid())
		return;

	Transform* parent = Parent.Get();
	Transform* child = Child.Get();

	if (child->Parent.IsValid()) {
		child->Parent.Get()->Children.erase(child->AssignedTo->Id);
	}

	child->Parent = Parent;
	child->bHasParentChanged = true;
	parent->Children.insert(std::pair<Entity, ComponentHandle<Transform>>(child->AssignedTo->Id, Child));
}
