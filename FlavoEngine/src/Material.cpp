#include "Material.h"
#include "Framework/FDraw.h"
#include "Framework/FUtils.h"
#include "OpenGL/glad/glad.h"

Engine::Material::Material() {
	ShaderProgram = Framework::FUtils::CompileShader("../../Resources/Shaders/DefaultShader.vert", "../../Resources/Shaders/DefaultShader.frag");
	TextureIndex = 0;
	ChangeColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

Engine::Material::~Material() {

}

void Engine::Material::AssignTexture(std::string Path) {
	TextureIndex = Framework::FDraw::BindTexture(Path);
}

void Engine::Material::ChangeColor(glm::vec4 NewColor) {
	Color = NewColor;
	glUseProgram(ShaderProgram);
	GLuint colorLoc = glGetUniformLocation(ShaderProgram, "ObjectColor");
	glUniform4f(colorLoc, Color.r, Color.g, Color.b, Color.a);
}
