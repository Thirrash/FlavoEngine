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
	ComponentHandle<Transform> transformHandle;
	ComponentHandle<MeshRenderer> rendererHandle;
	for (Entity entity : es.entities_with_components(transformHandle, rendererHandle)) {
		if (!transformHandle.IsValid() || !rendererHandle.IsValid()) {
			LogW("Handle not valid for: ", entity.id().id());
			continue;
		}

		MeshRenderer* renderer = rendererHandle.Get();
		Transform* transform = transformHandle.Get();
		SetTransform(transform, renderer->CurrentMat.ShaderProgram);
		RenderMesh(renderer->VAOIndex, renderer->CurrentMat.ShaderProgram, renderer->CurrentMat.TextureIndex, renderer->CurrentMesh.NoIndices);
	}
}

void Engine::GraphicSystem::SetTransform(Transform* Trans, int ShaderProgram) {
	//View matrix
	Camera* camera = SceneManager::GetCurrent()->MainCamera.Get()->Get<Camera>().Get();
	Transform* cameraTransform = SceneManager::GetCurrent()->MainCamera.Get()->Get<Transform>().Get();
	glm::vec3 eye = cameraTransform->Position;
	glm::vec3 dir = glm::normalize(cameraTransform->Forward);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::lookAt(eye, eye + dir, up);
	camera->ViewMatrix = view;

	//Projection matrix
	int w, h;
	glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);
	glm::mat4 projection = glm::perspective(45.0f, (float)w / (float)h, 0.001f, 50.0f);
	camera->PerspectiveMatrix = projection;

	//WVP matrix
	glUseProgram(ShaderProgram);
	GLuint projLoc = glGetUniformLocation(ShaderProgram, "Projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);
	GLuint viewLoc = glGetUniformLocation(ShaderProgram, "View");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
	GLuint worldLoc = glGetUniformLocation(ShaderProgram, "World");
	glUniformMatrix4fv(worldLoc, 1, GL_FALSE, &Trans->World[0][0]);
}

void Engine::GraphicSystem::RenderMesh(unsigned int VAOIndex, int ShaderProgram, unsigned int TextureIndex, unsigned int NoIndices) {
	glUseProgram(ShaderProgram);
	glBindVertexArray(VAOIndex);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureIndex);
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