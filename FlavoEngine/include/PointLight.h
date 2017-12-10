#pragma once

#include "LightBase.h"

namespace Engine
{
	class PointLight : public LightBase<PointLight>
	{
		/*** Constants ***/
		/*** Ctors ***/
	public:
		PointLight();
		virtual ~PointLight();

		/*** Fields ***/
	public:
		float Constant;
		float Linear;
		float Quadratic;

		/*** Methods ***/
	public:
		void SetParams(float NewConstant, float NewLinear, float NewQuadratic);
	};
}