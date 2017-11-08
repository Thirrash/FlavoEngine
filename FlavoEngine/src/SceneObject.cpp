#include "SceneObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Transform.h"

Engine::SceneObject::SceneObject(Entity Id) {
	this->Id = Id;

	Add<Transform>();
}

Engine::SceneObject::~SceneObject() {
	Id.destroy();
}

bool Engine::SceneObject::IsNull() {
	return Id.valid();
}
