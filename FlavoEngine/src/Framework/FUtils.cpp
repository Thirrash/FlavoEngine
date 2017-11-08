#include "FUtils.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <stb_image.h>
#include "Debug.h"

Framework::FUtils::FUtils() {}

string Framework::FUtils::LoadShaderFromFile(string Path) {
	ifstream shaderFile(Path);
	string shaderString((istreambuf_iterator<char>(shaderFile)), (istreambuf_iterator<char>()));
	shaderFile.close();
	return shaderString;
}

bool Framework::FUtils::CheckShaderCompilation(int ShaderIndex, string ShaderType) {
	int success;
	char infoLog[512];
	glGetShaderiv(ShaderIndex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(ShaderIndex, 512, NULL, infoLog);
		LogR(ShaderType + " error");
		LogD(infoLog);
		return false;
	}

	return true;
}

double Framework::FUtils::GetTime() {
	return glfwGetTime();
}

bool Framework::FUtils::CheckGameLoopClose() {
	return glfwWindowShouldClose(glfwGetCurrentContext());
}

void Framework::FUtils::PollEvents() {
	glfwPollEvents();
}

void Framework::FUtils::Terminate() {
	glfwTerminate();
}

int Framework::FUtils::CompileShader(string VertexPath, string FragmentPath) {
	int shaderProgramIndex = -1;

	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	string vertexString = LoadShaderFromFile(VertexPath);
	const char* vertexChars = &vertexString[0u];
	glShaderSource(vertexShader, 1, &vertexChars, NULL);
	glCompileShader(vertexShader);
	CheckShaderCompilation(vertexShader, "Vertex shader");

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	string fragmentString = LoadShaderFromFile(FragmentPath);
	const char* fragmentChars = &fragmentString[0u];
	glShaderSource(fragmentShader, 1, &fragmentChars, NULL);
	glCompileShader(fragmentShader);
	CheckShaderCompilation(fragmentShader, "Fragment shader");

	shaderProgramIndex = glCreateProgram();
	glAttachShader(shaderProgramIndex, vertexShader);
	glAttachShader(shaderProgramIndex, fragmentShader);
	glLinkProgram(shaderProgramIndex);
	CheckShaderCompilation(shaderProgramIndex, "Shader linking");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgramIndex;
}

unsigned char* Framework::FUtils::LoadTextureFromFile(string Path, int* Width, int* Height, int* NoChannels) {
	stbi_set_flip_vertically_on_load(true);
	unsigned char* loaded = stbi_load(Path.c_str(), Width, Height, NoChannels, 0);
	return loaded;
}

void Framework::FUtils::DeallocateTextureFile(unsigned char* Data) {
	stbi_image_free(Data);
}
