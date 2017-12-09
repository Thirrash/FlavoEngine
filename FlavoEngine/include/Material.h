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

		glm::vec3 Diffuse;
		glm::vec3 Ambient;
		glm::vec3 Specular;
		float Shininess;

		/*** Methods ***/
	public:
		void AssignTexture(std::string Path);
		void ChangeColor(glm::vec4 NewColor);
		void ChangeProperties(glm::vec3 NewDiffuse, glm::vec3 NewAmbient, glm::vec3 NewSpecular, float Shininess);
	};
}