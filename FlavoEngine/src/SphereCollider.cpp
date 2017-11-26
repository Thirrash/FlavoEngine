#include "SphereCollider.h"
#include "Transform.h"

Engine::SphereCollider::SphereCollider() : Collider() {

}

Engine::SphereCollider::~SphereCollider() {

}

void Engine::SphereCollider::SetRadius(float Radius) {
	this->Radius = Radius;
	SetLocalBoundingBox(-Radius, Radius, -Radius, Radius, -Radius, Radius);
	bIsDirty = true;
}

bool Engine::SphereCollider::CheckLineCollision(const glm::vec3& LineOrigin, const glm::vec3& LineEnd, Transform* Trans, glm::vec3& CollisionPoint) {
	glm::vec3 lineDir = LineEnd - LineOrigin;
	float a = lineDir.x * lineDir.x + lineDir.y * lineDir.y + lineDir.z * lineDir.z;
	float b = 2.0f * (LineOrigin.x * lineDir.x + LineOrigin.y * lineDir.y + LineOrigin.z * lineDir.z - lineDir.x * Trans->Position.x - lineDir.y * Trans->Position.y - lineDir.z * Trans->Position.z);
	float c = LineOrigin.x * LineOrigin.x - 2.0f * LineOrigin.x * Trans->Position.x + Trans->Position.x * Trans->Position.x +
		LineOrigin.y * LineOrigin.y - 2.0f * LineOrigin.y * Trans->Position.y + Trans->Position.y * Trans->Position.y +
		LineOrigin.z * LineOrigin.z - 2.0f * LineOrigin.z * Trans->Position.z + Trans->Position.z * Trans->Position.z -
		Radius * Radius;
	float d = b * b - 4.0f * a * c;
	float t = -1.0f;
	if (d >= 0) {
		float t1 = (-b - glm::sqrt(d)) / (2.0f * a);
		float t2 = (-b + glm::sqrt(d)) / (2.0f * a);
		t = (t1 > t2) ? t2 : t1;
		CollisionPoint = LineOrigin + t * lineDir;
		return true;
	}

	return false;
}
