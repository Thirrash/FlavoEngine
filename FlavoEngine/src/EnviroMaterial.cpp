#include "EnviroMaterial.h"
#include "Framework/FDraw.h"
#include "Framework/FUtils.h"
#include "OpenGL/glad/glad.h"

Engine::EnviroMaterial::EnviroMaterial() {
	ShaderProgram = Framework::FUtils::CompileShader("../../Resources/Shaders/EnviroShader.vert", "../../Resources/Shaders/EnviroShader.frag");

	ChangeProperties(0.0f, 2.3f);
}

Engine::EnviroMaterial::~EnviroMaterial() {

}

void Engine::EnviroMaterial::ChangeProperties(float Reflect, float Refract) {
	this->Reflect = Reflect;
	this->Refract = Refract;

	glUseProgram(ShaderProgram);
	GLuint reflectLoc = glGetUniformLocation(ShaderProgram, "MatProp.Reflect");
	glUniform1f(reflectLoc, Reflect);
	GLuint refractLoc = glGetUniformLocation(ShaderProgram, "MatProp.Refract");
	glUniform1f(refractLoc, Refract);
}
