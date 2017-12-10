#pragma once

#include "InternalComponent.h"
#include <glm/glm.hpp>

namespace Engine
{
	template<class C>
	class LightBase : public InternalComponent<C>
	{
		/*** Constants ***/
		/*** Ctors ***/
	public:
		LightBase() { Color = glm::vec3(1.0f, 1.0f, 1.0f); }
		virtual ~LightBase() { }

		/*** Fields ***/
	public:
		glm::vec3 Color;
		float Intensity;
		bool bIsDirty;

		/*** Methods ***/
	public:
		void SetColor(glm::vec3 NewColor) { Color = NewColor; glm::normalize(Color); bIsDirty = true; }
		void SetIntensity(float NewIntensity) { Intensity = NewIntensity; bIsDirty = true; }
	};
}