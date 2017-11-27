#pragma once

#include "InternalComponent.h"
#include <glm/glm.hpp>
#include "Input.h"

namespace Engine
{
	class GLFWwindow;

	struct Ray
	{
		glm::vec3 Origin;
		glm::vec3 Dir;
		glm::vec3 End;

		Ray(glm::vec3 Origin, glm::vec3 End) : Origin(Origin), End(End) {
			Dir = End - Origin;
		}
	};

	class Camera : public InternalComponent<Camera>, public Receiver<MouseInput>
	{
		friend class GraphicSystem;

		/*** Constants ***/
		/*** Ctors ***/
	public:
		Camera();
		virtual ~Camera();

		/*** Fields ***/
	public:
		int MouseX;
		int MouseY;

	private:
		glm::mat4 ViewMatrix;
		glm::mat4 PerspectiveMatrix;

		/*** Methods ***/
	public:
		Ray GetRayFromMousePosition(float RayDepth);

		void configure(EventManager& event_manager);
		void receive(const MouseInput& Input);
	};
}