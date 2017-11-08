#pragma once

#include "EntityX.h"
#include "Input.h"

class GLFWwindow;

namespace Engine
{
	class InputSystem : public System<InputSystem>
	{
		/*** Constants ***/
		/*** Ctors ***/
	public:
		InputSystem();
		~InputSystem();

		/*** Fields ***/
	private:
		double LastMouseX;
		double LastMouseY;
		MouseInput* PendingMouse;

		/*** Methods ***/
	public:
		void Update(EntityManager& es, EventManager& events, TimeDelta dt) override;

	private:
		bool CheckKey(EKeyCode KeyCode);
		void MouseCallback(GLFWwindow* Window, double X, double Y);
		void ScrollCallback(GLFWwindow* Window, double XOffset, double YOffset);

		void SetMouseMovement(double X, double Y);
		void SetMouseScroll(double XOffset);
	};
}