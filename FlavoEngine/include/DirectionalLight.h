#pragma once

#include "LightBase.h"

namespace Engine
{
	class DirectionalLight : public LightBase<DirectionalLight>
	{
		/*** Constants ***/
		/*** Ctors ***/
	public:
		DirectionalLight();
		virtual ~DirectionalLight();

		/*** Fields ***/
	public:
		glm::vec3 Direction;

		/*** Methods ***/
	public:
		void SetDirection(glm::vec3 NewDirection);
	};
}