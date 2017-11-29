#include "BoxCollider.h"
#include "Transform.h"
#include "Debug.h"

Engine::BoxCollider::BoxCollider() {

}

Engine::BoxCollider::~BoxCollider() {

}

void Engine::BoxCollider::SetBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax) {
	SetLocalBoundingBox(xMin, xMax, yMin, yMax, zMin, zMax);
	bIsDirty = true;
}

//Without collision point implementation
bool Engine::BoxCollider::CheckLineCollision(const glm::vec3& LineOrigin, const glm::vec3& LineEnd, Transform* Trans, glm::vec3& CollisionPoint) {
	//LogA(WorldBoundingBox[0].x, WorldBoundingBox[1].x, WorldBoundingBox[2].x);
	glm::vec3 d = (LineEnd - LineOrigin) * 0.5f;
	glm::vec3 min = glm::vec3(WorldBoundingBox[0].x, WorldBoundingBox[1].x, WorldBoundingBox[2].x);
	glm::vec3 max = glm::vec3(WorldBoundingBox[0].y, WorldBoundingBox[1].y, WorldBoundingBox[2].y);
	glm::vec3 e = (max - min) * 0.5f;
	glm::vec3 c = LineOrigin + d - (min + max) * 0.5f;
	glm::vec3 ad = glm::vec3(fabsf(d.x), fabsf(d.y), fabsf(d.z));

	if (fabsf(c[0]) > e[0] + ad[0])
		return false;
	if (fabsf(c[1]) > e[1] + ad[1])
		return false;
	if (fabsf(c[2]) > e[2] + ad[2])
		return false;

	if (fabsf(d[1] * c[2] - d[2] * c[1]) > e[1] * ad[2] + e[2] * ad[1])
		return false;
	if (fabsf(d[2] * c[0] - d[0] * c[2]) > e[2] * ad[0] + e[0] * ad[2])
		return false;
	if (fabsf(d[0] * c[1] - d[1] * c[0]) > e[0] * ad[1] + e[1] * ad[0])
		return false;

	//LogW("GUD");
	return true;
}