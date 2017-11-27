#include "Camera.h"
#include "OpenGL/GLFW/glfw3.h"
#include "glm/gtc/matrix_inverse.hpp"
#include "SceneObject.h"
#include "Transform.h"
#include "Debug.h"

Engine::Camera::Camera() {

}

Engine::Camera::~Camera() {

}

Engine::Ray Engine::Camera::GetRayFromMousePosition(float RayDepth) {
	int width, height;
	glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
	glm::vec4 rayClip(
		(2.0f * MouseX) / width - 1.0f,
		1.0f - (2.0f * MouseY) / height,
		-1.0f,
		1.0f
	);

	//LogD(MouseX / width, MouseY / height);
	glm::vec4 eye = glm::inverse(PerspectiveMatrix) * rayClip;
	eye.z = -1.0f;
	eye.w = 0.0f;

	glm::vec3 world = (glm::inverse(ViewMatrix) * eye);
	world = glm::normalize(world);
	//LogB(world.x, world.y, world.z);
	//LogA(AssignedTo->Get<Transform>().Get()->Forward.x, AssignedTo->Get<Transform>().Get()->Forward.y, AssignedTo->Get<Transform>().Get()->Forward.z);

	return Ray(AssignedTo->Get<Transform>().Get()->Position, AssignedTo->Get<Transform>().Get()->Position + RayDepth * world);
}

void Engine::Camera::configure(EventManager& event_manager) {
	event_manager.subscribe<MouseInput>(*this);
}

void Engine::Camera::receive(const MouseInput& Input) {
	if (glfwGetInputMode(glfwGetCurrentContext(), GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
		return;

	int width, height;
	glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
	MouseX = Input.X;
	MouseY = Input.Y;
}

