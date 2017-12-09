#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Engine
{
	class Material
	{
		/*** Constants ***/
		/*** Ctors ***/
	public:
		Material();
		virtual ~Material();

		/*** Fields ***/
	public:
		unsigned int TextureIndex;
		unsigned int ShaderProgram;
		glm::vec4 Color;

		/*** Methods ***/
	public:
		void AssignTexture(std::string Path);
		void ChangeColor(glm::vec4 NewColor);
	};
}