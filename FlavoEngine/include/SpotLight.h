#pragma once

#include "LightBase.h"

namespace Engine
{
	class SpotLight : public LightBase<SpotLight>
	{
		/*** Constants ***/
		/*** Ctors ***/
	public:
		SpotLight();
		virtual ~SpotLight();

		/*** Fields ***/
	public:
		glm::vec3 Direction;
		float Cutoff;
		float OuterCutoff;

		/*** Methods ***/
	public:
		void SetParams(glm::vec3 NewDirection, float NewCutoff, float OuterCutoff);
	};
}