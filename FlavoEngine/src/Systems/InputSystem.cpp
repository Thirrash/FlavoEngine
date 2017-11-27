#include "Systems/InputSystem.h"
#include <GLFW/glfw3.h>
#include "Debug.h"

Engine::InputSystem::InputSystem() {
	GLFWwindow* Window = glfwGetCurrentContext();
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	int width, height;
	glfwGetWindowSize(Window, &width, &height);
	PendingMouse = new MouseInput(width, height, 0.0);
	LastMouseX = width;
	LastMouseY = height;

	glfwSetWindowUserPointer(Window, this);
	glfwSetCursorPosCallback(Window, [](GLFWwindow* Window, double X, double Y) {static_cast<InputSystem*>(glfwGetWindowUserPointer(Window))->MouseCallback(Window, X, Y); });
	glfwSetScrollCallback(Window, [](GLFWwindow* Window, double XOffset, double YOffset) {static_cast<InputSystem*>(glfwGetWindowUserPointer(Window))->ScrollCallback(Window, XOffset, YOffset); });
}

Engine::InputSystem::~InputSystem() {

}

void Engine::InputSystem::Update(EntityManager& es, EventManager& events, TimeDelta dt) {
	static bool bIsCursorHidden = true;
	static float lastRInput = 0.0f;

	events.emit<MouseInput>(PendingMouse->X, PendingMouse->Y, PendingMouse->Scroll);
	LastMouseX = PendingMouse->X;
	LastMouseY = PendingMouse->Y;
	PendingMouse->Scroll = 0.0;

	if (CheckKey(EKeyCode::R) && lastRInput > 1.0f) {
		bIsCursorHidden = !bIsCursorHidden;
		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, (bIsCursorHidden) ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
		lastRInput = 0.0f;
	}

	lastRInput += dt;
}

bool Engine::InputSystem::CheckKey(EKeyCode KeyCode) {
	return (glfwGetKey(glfwGetCurrentContext(), KeyCode) == GLFW_PRESS) ? true : false;
}

void Engine::InputSystem::MouseCallback(GLFWwindow* Window, double X, double Y) {
	SetMouseMovement(X, Y);
}

void Engine::InputSystem::ScrollCallback(GLFWwindow* Window, double XOffset, double YOffset) {
	SetMouseScroll(XOffset);
}

void Engine::InputSystem::SetMouseMovement(double X, double Y) {
	PendingMouse->X = X;
	PendingMouse->Y = Y;
}

void Engine::InputSystem::SetMouseScroll(double XOffset) {
	PendingMouse->Scroll += XOffset;
}
