#include "Systems/GraphicSystem.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Transform.h"
#include "MeshRenderer.h"
#include "Debug.h"
#include "Color.h"
#include "Framework/FDraw.h"
#include "SceneManager.h"
#include "Scene.h"
#include "SceneObjectHandle.h"
#include "SceneObject.h"
#include "Maths.h"

Engine::GraphicSystem::GraphicSystem() {
	glEnable(GL_DEPTH_TEST);
}

Engine::GraphicSystem::~GraphicSystem() {

}

void Engine::GraphicSystem::Update(EntityManager& es, EventManager& events, TimeDelta dt) {
	DrawBackground(Color(0.1f, 0.2f, 0.3f, 1.0f));

	ComponentHandle<Transform> transformHandle;
	ComponentHandle<MeshRenderer> rendererHandle;
	for (Entity entity : es.entities_with_components(transformHandle, rendererHandle)) {
		if (!transformHandle.IsValid() || !rendererHandle.IsValid()) {
			continue;
		}

		MeshRenderer* renderer = rendererHandle.Get();
		Transform* transform = transformHandle.Get();
		SetTransform(*transform, renderer->ShaderProgram);
		RenderMesh(renderer->VAOIndex, renderer->ShaderProgram, renderer->TextureIndex, renderer->CurrentMesh.NoIndices);
	}

	FinalizeRender();
}

void Engine::GraphicSystem::SetTransform(const Engine::Transform& Trans, int ShaderProgram) {
	//View matrix
	Transform* cameraTransform = SceneManager::GetCurrent()->MainCamera.Get()->Get<Transform>().Get();
	glm::vec3 eye = glm::vec3(cameraTransform->Position.X, cameraTransform->Position.Y, cameraTransform->Position.Z);

	glm::vec3 dir = glm::vec3(0.0f);
	dir.x = cos(glm::radians(cameraTransform->Rotation.X)) * cos(glm::radians(cameraTransform->Rotation.Y));
	dir.y = sin(glm::radians(cameraTransform->Rotation.X));
	dir.z = cos(glm::radians(cameraTransform->Rotation.X)) * sin(glm::radians(cameraTransform->Rotation.Y));
	dir = glm::normalize(dir);

	glm::vec3 up(0.0f, 1.0f, 0.0f);

	glm::mat4 view = glm::lookAt(eye, eye + dir, up);

	//Projection matrix
	int w, h;
	glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);
	glm::mat4 projection = glm::perspective(45.0f, (float)w / (float)h, 0.001f, 50.0f);

	//WVP matrix
	glm::mat4 WVP = projection * view * Trans.World;
	GLuint wvpLoc = glGetUniformLocation(ShaderProgram, "WorldViewProjection");
	glUniformMatrix4fv(wvpLoc, 1, GL_FALSE, &WVP[0][0]);
}

void Engine::GraphicSystem::RenderMesh(unsigned int VAOIndex, int ShaderProgram, unsigned int TextureIndex, unsigned int NoIndices) {
	glUseProgram(ShaderProgram);
	glBindTexture(GL_TEXTURE0, TextureIndex);
	glBindVertexArray(VAOIndex);
	glDrawElements(GL_TRIANGLES, NoIndices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Engine::GraphicSystem::DrawBackground(Engine::Color BckColor) {
	glClearColor(BckColor.R, BckColor.G, BckColor.B, BckColor.A);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::GraphicSystem::FinalizeRender() {
	glfwSwapBuffers(glfwGetCurrentContext());
}