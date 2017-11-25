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
	float* Vertices;
	unsigned int* Indices;
	std::vector<SceneObjectHandle> Cubes;
	float StartTime;

	/*** Methods ***/
public:
	void Start() override;
	void Update(double DeltaTime) override;

	void configure(EventManager& event_manager);
	void receive(const MouseInput& Input);

private:
	SceneObjectHandle CreateCube(glm::vec3 pos, std::string texturePath);
};