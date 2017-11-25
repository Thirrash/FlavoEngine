#include "..\include\Transform.h"

Engine::Transform::Transform() : bIsDirty(true), bHasParentChanged(true) {
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	LocalScale = glm::vec3(1.0f, 1.0f, 1.0f);
	LocalRotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
}

Engine::Transform::~Transform() {

}

void Engine::Transform::SetLocalPosition(glm::vec3 Pos) {
	LocalPosition = Pos;
	Position = Pos; //temporary
	bIsDirty = true;
}

void Engine::Transform::SetLocalRotation(glm::quat Rot) {
	LocalRotation = Rot;
	Rotation = Rot; //temporary
	bIsDirty = true;
}

void Engine::Transform::SetLocalScale(glm::vec3 Scale) {
	LocalScale = Scale;
	this->Scale = Scale; //temporary
	bIsDirty = true;
}
