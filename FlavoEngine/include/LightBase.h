#pragma once

#include "InternalComponent.h"
#include <glm/glm.hpp>

namespace Engine
{
	class LightBase : InternalComponent<LightBase>
	{
		/*** Constants ***/
		/*** Ctors ***/
	public:
		LightBase();
		virtual ~LightBase();

		/*** Fields ***/
	public:
		glm::vec4 Color;

		/*** Methods ***/
	};
}