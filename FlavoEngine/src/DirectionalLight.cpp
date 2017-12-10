#include "DirectionalLight.h"

Engine::DirectionalLight::DirectionalLight() {
	SetDirection(glm::vec3(0.0f, -1.0f, 0.0f));
	SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	SetIntensity(1.0f);
}

Engine::DirectionalLight::~DirectionalLight() {

}

void Engine::DirectionalLight::SetDirection(glm::vec3 NewDirection) {
	bIsDirty = true;
	Direction = NewDirection;
}
