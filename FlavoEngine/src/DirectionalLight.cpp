#include "DirectionalLight.h"

Engine::DirectionalLight::DirectionalLight() {
	Direction = glm::vec3(0.0f, -1.0f, 0.0f);
	Color = glm::vec3(1.0f, 1.0f, 1.0f);
}

Engine::DirectionalLight::~DirectionalLight() {

}
