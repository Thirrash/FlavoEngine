#include "Collider.h"

Engine::Collider::Collider() : bIsDirty(false), CurrentCells(Engine::GlmVec3Comparer()) {
	LocalBoundingBox = std::vector<glm::vec2>(3);
	WorldBoundingBox = std::vector<glm::vec2>(3);
}

Engine::Collider::~Collider() {

}

void Engine::Collider::SetLocalBoundingBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax) {
	LocalBoundingBox[0] = glm::vec2(xMin, xMax);
	LocalBoundingBox[1] = glm::vec2(yMin, yMax);
	LocalBoundingBox[2] = glm::vec2(zMin, zMax);
}

bool Engine::GlmVec3Comparer::operator()(const glm::vec3& first, const glm::vec3& second) const {
	return (first.x != second.x) ? (first.x < second.x) : (first.y != second.y) ? (first.y < second.y) : (first.z != second.z) ? (first.z < second.z) : false;
}
