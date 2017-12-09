#include "FDraw.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Color.h"
#include "FUtils.h"
#include "Debug.h"
#include "Mesh.h"
#include "Transform.h"

Framework::FDraw::FDraw() {}

unsigned int Framework::FDraw::BindVAO(Engine::Mesh& Data) {
	unsigned int VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Data.NoVertices, Data.Vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * Data.NoIndices, Data.Indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(float), (void*)(3 * sizeof(float))); //normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); //uv
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return VAO;
}

unsigned int Framework::FDraw::BindTexture(string Path) {
	unsigned int textureIndex;
	glGenTextures(1, &textureIndex);
	glBindTexture(GL_TEXTURE_2D, textureIndex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, noChannels;
	unsigned char* data = FUtils::LoadTextureFromFile(Path, &width, &height, &noChannels);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		LogR("Loaded image data is null", Path);
	}

	FUtils::DeallocateTextureFile(data);
	return textureIndex;
}