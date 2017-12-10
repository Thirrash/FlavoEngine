#include "Material.h"
#include "Framework/FDraw.h"
#include "Framework/FUtils.h"
#include "OpenGL/glad/glad.h"

Engine::Material::Material() {
	ShaderProgram = Framework::FUtils::CompileShader("../../Resources/Shaders/DefaultShader.vert", "../../Resources/Shaders/DefaultShader.frag");
	TextureIndex = 0;
	ChangeColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	ChangeProperties(glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.18f, 0.18f, 0.18f), glm::vec3(0.9f, 0.9f, 0.9f), 50.0f);
}

Engine::Material::~Material() {

}

void Engine::Material::AssignTexture(std::string Path) {
	TextureIndex = Framework::FDraw::BindTexture(Path);
}

void Engine::Material::ChangeColor(glm::vec4 NewColor) {
	Color = NewColor;
	glUseProgram(ShaderProgram);
	GLuint colorLoc = glGetUniformLocation(ShaderProgram, "MatProp.ObjectColor");
	glUniform4f(colorLoc, Color.r, Color.g, Color.b, Color.a);
}

void Engine::Material::ChangeProperties(glm::vec3 NewDiffuse, glm::vec3 NewAmbient, glm::vec3 NewSpecular, float Shininess) {
	Diffuse = NewDiffuse;
	Ambient = NewAmbient;
	Specular = NewSpecular;
	this->Shininess = Shininess;

	glUseProgram(ShaderProgram);
	GLuint diffuseLoc = glGetUniformLocation(ShaderProgram, "MatProp.Diffuse");
	glUniform3f(diffuseLoc, Diffuse.x, Diffuse.y, Diffuse.z);
	GLuint ambientLoc = glGetUniformLocation(ShaderProgram, "MatProp.Ambient");
	glUniform3f(ambientLoc, Ambient.x, Ambient.y, Ambient.z);
	GLuint specularLoc = glGetUniformLocation(ShaderProgram, "MatProp.Specular");
	glUniform3f(specularLoc, Specular.x, Specular.y, Specular.z);
	GLuint shininessLoc = glGetUniformLocation(ShaderProgram, "MatProp.Shininess");
	glUniform1f(shininessLoc, Shininess);
}
