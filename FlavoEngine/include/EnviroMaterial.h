#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Engine
{
	class EnviroMaterial
	{
		/*** Constants ***/
		/*** Ctors ***/
	public:
		EnviroMaterial();
		virtual ~EnviroMaterial();

		/*** Fields ***/
	public:
		unsigned int ShaderProgram;

		float Reflect;
		float Refract;

		/*** Methods ***/
	public:
		void ChangeProperties(float Reflect, float Refract);
	};
}