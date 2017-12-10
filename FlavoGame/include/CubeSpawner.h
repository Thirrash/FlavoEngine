#pragma once

#include "UserComponent.h"
#include "SceneObjectHandle.h"
#include "Vector3.h"
#include <string>
#include "Input.h"
#include <vector>
#include "OpenGL/glm/glm.hpp"

using namespace Engine;
class CubeSpawner : public UserComponent, public Receiver<MouseInput>
{
	/*** Constants ***/
	/*** Ctors ***/
public:
	CubeSpawner();

	/*** Fields ***/
private:
	std::vector<SceneObjectHandle> Point;
	SceneObjectHandle Dir;
	SceneObjectHandle Spot;

	float StartTime;
	MouseInput LastInput;

	/*** Methods ***/
public:
	void Start() override;
	void Update(double DeltaTime) override;

	void configure(EventManager& event_manager);
	void receive(const MouseInput& Input);

private:
	SceneObjectHandle CreatePointLight(glm::vec3 pos, glm::vec3 color, float intensity, std::string texturePath);
};