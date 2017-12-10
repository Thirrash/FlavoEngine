#include "SpotLight.h"

Engine::SpotLight::SpotLight() {
	SetParams(glm::vec3(1.0f, 0.0f, 0.0f), glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)));
	SetIntensity(1.0f);
	SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
}

Engine::SpotLight::~SpotLight() {
}

void Engine::SpotLight::SetParams(glm::vec3 NewDirection, float NewCutoff, float OuterCutoff) {
	Direction = NewDirection;
	Cutoff = NewCutoff;
	this->OuterCutoff = OuterCutoff;
	bIsDirty = true;
}
