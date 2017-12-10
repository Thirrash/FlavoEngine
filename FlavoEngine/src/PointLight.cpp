#include "..\include\PointLight.h"

Engine::PointLight::PointLight() {
	SetParams(1.0f, 0.3f, 0.1f);
	SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	SetIntensity(1.0f);
}

Engine::PointLight::~PointLight() {

}

void Engine::PointLight::SetParams(float NewConstant, float NewLinear, float NewQuadratic) {
	Constant = NewConstant;
	Linear = NewLinear;
	Quadratic = NewQuadratic;
	bIsDirty = true;
}
