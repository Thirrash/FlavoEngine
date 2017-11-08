#include "..\include\Transform.h"

Engine::Transform::Transform() : bIsDirty(true), bHasParentChanged(true) {
	Scale = Vector3(1.0f, 1.0f, 1.0f);
	LocalScale = Vector3(1.0f, 1.0f, 1.0f);
}

Engine::Transform::~Transform() {

}

void Engine::Transform::SetLocalPosition(Vector3 Pos) {
	LocalPosition = Pos;
	Position = Pos; //temporary
	bIsDirty = true;
}

void Engine::Transform::SetLocalRotation(Vector3 Rot) {
	LocalRotation = Rot;
	Rotation = Rot; //temporary
	bIsDirty = true;
}

void Engine::Transform::SetLocalScale(Vector3 Scale) {
	LocalScale = Scale;
	this->Scale = Scale; //temporary
	bIsDirty = true;
}
