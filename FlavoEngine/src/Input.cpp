#include "Input.h"
#include <GLFW/glfw3.h>

Engine::MouseInput::MouseInput(double X, double Y, double Scroll) : X(X), Y(Y), Scroll(Scroll) {

}

bool Engine::MouseInput::operator==(const MouseInput& Other) {
	return (X != Other.X) ? false : (Y != Other.Y) ? false : (Scroll != Other.Scroll) ? false : true;
}

bool Engine::MouseInput::operator!=(const MouseInput& Other) {
	return (X == Other.X) ? false : (Y == Other.Y) ? false : (Scroll == Other.Scroll) ? false : true;
}

Engine::MouseInput Engine::MouseInput::Zero = Engine::MouseInput(0.0, 0.0, 0.0);

bool Engine::Input::IsKeyDown(EKeyCode Key) {
	return (glfwGetKey(glfwGetCurrentContext(), Key) == GLFW_PRESS) ? true : false;
}
