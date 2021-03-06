#define GLM_ENABLE_EXPERIMENTAL

#include "Systems/GraphicSystem.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "Transform.h"
#include "Framework/FUtils.h"
#include "MeshRenderer.h"
#include "EnviroMeshRenderer.h"
#include "Debug.h"
#include "Color.h"
#include "Framework/FDraw.h"
#include "SceneManager.h"
#include "Scene.h"
#include "SceneObjectHandle.h"
#include "SceneObject.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Maths.h"

Engine::GraphicSystem::GraphicSystem() {
	glEnable(GL_DEPTH_TEST);

	raymarchShader_ = Framework::FUtils::CompileShader("../../Resources/Shaders/Raymarching.vert", "../../Resources/Shaders/Raymarching.frag");
}

Engine::GraphicSystem::~GraphicSystem() {

}

void Engine::GraphicSystem::configure(EventManager& event_manager) {
	event_manager.subscribe<MouseInput>(*this);
}

void Engine::GraphicSystem::receive(const MouseInput& Input) {
	mousePos_ = glm::vec2(Input.X, Input.Y);
}

void Engine::GraphicSystem::Update(EntityManager& es, EventManager& events, TimeDelta dt) {
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_X) == GLFW_PRESS && !xPressed_) {
		lensToggle_ = (lensToggle_ == 0.0f) ? 1.0f : 0.0f;
		int toggleLoc = glGetUniformLocation(postprocess_.shaderProgram, "lensToggle");
		glUniform1f(toggleLoc, lensToggle_);
		xPressed_ = true;
	} else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_X) == GLFW_RELEASE) {
		xPressed_ = false;
	}


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindFramebuffer(GL_FRAMEBUFFER, postprocess_.framebuffer);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ComponentHandle<DirectionalLight> dirHandle;
	for (Entity entity : es.entities_with_components(dirHandle)) {
		break;
	}

	ComponentHandle<SpotLight> spotHandle;
	for (Entity entity : es.entities_with_components(spotHandle)) {
		break;
	}

	std::vector<PointLight*> pointLights;
	ComponentHandle<PointLight> pointHandle;
	for (Entity entity : es.entities_with_components(pointHandle)) {
		pointLights.push_back(pointHandle.Get());
	}

	ComponentHandle<Transform> transformHandle;
	ComponentHandle<MeshRenderer> rendererHandle;
	for (Entity entity : es.entities_with_components(transformHandle, rendererHandle)) {
		if (!transformHandle.IsValid() || !rendererHandle.IsValid()) {
			LogW("Handle not valid for: ", entity.id().id());
			continue;
		}

		MeshRenderer* renderer = rendererHandle.Get();
		Transform* transform = transformHandle.Get();

		glUseProgram(renderer->CurrentMat.ShaderProgram);
		SetTransform(transform, renderer->CurrentMat.ShaderProgram);
		SetDirectionalLight(renderer->CurrentMat.ShaderProgram, dirHandle.Get());
		SetSpotLight(renderer->CurrentMat.ShaderProgram, spotHandle.Get());
		for (int i = 0; i < pointLights.size() && i < 4; i++) {
			SetPointLight(renderer->CurrentMat.ShaderProgram, pointLights[i], i);
		}
		RenderMesh(renderer->VAOIndex, renderer->CurrentMat.ShaderProgram, renderer->CurrentMat.TextureIndex, renderer->CurrentMesh.NoIndices);
	}


	ComponentHandle<EnviroMeshRenderer> enviroRendererHandle;
	for (Entity entity : es.entities_with_components(transformHandle, enviroRendererHandle)) {
		if (!transformHandle.IsValid() || !enviroRendererHandle.IsValid()) {
			LogW("Handle not valid for: ", entity.id().id());
			continue;
		}

		EnviroMeshRenderer* renderer = enviroRendererHandle.Get();
		Transform* transform = transformHandle.Get();

		glUseProgram(renderer->CurrentMat.ShaderProgram);
		SetTransform(transform, renderer->CurrentMat.ShaderProgram);
		RenderMesh(renderer->VAOIndex, renderer->CurrentMat.ShaderProgram, skybox_.textureId_, renderer->CurrentMesh.NoIndices);
	}

	DrawSkybox();
	postprocess_.OnZkey();

	int width, height;
	glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
	glUseProgram(raymarchShader_);
	int screenSizeLoc = glGetUniformLocation(raymarchShader_, "ScreenSize");
	glUniform2f(screenSizeLoc, width, height);
	int eyePos = glGetUniformLocation(raymarchShader_, "EyePos");
	glm::vec3 eyePosition = SceneManager::GetCurrent()->MainCamera.Get()->Get<Transform>().Get()->Position;
	glUniform3f(eyePos, eyePosition.x, eyePosition.y, eyePosition.z);
	LogB(eyePosition.x, eyePosition.y, eyePosition.z);
	int pitchYawLoc = glGetUniformLocation(raymarchShader_, "PitchYaw");
	glm::vec3 cameraRot = glm::eulerAngles(SceneManager::GetCurrent()->MainCamera.Get()->Get<Transform>().Get()->LocalRotation);
	glUniform2f(pitchYawLoc, cameraRot.x, cameraRot.y);
	int lookDirLoc = glGetUniformLocation(raymarchShader_, "LookDir");
	glm::vec3 lookDir = glm::normalize(SceneManager::GetCurrent()->MainCamera.Get()->Get<Transform>().Get()->Forward);
	glUniform3f(lookDirLoc, lookDir.x, lookDir.y, lookDir.z);
	glBindVertexArray(postprocess_.vaoIndex);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//------Postprocess
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(postprocess_.shaderProgram);
	int windowsSizeLoc = glGetUniformLocation(postprocess_.shaderProgram, "ScreenSize");
	glUniform2f(windowsSizeLoc, width, height);
	int mousePosLoc = glGetUniformLocation(postprocess_.shaderProgram, "MousePos");
	glUniform2f(mousePosLoc, mousePos_.x, mousePos_.y);

	glBindVertexArray(postprocess_.vaoIndex);
	glDisable(GL_DEPTH_TEST);
	
	glBindTexture(GL_TEXTURE_2D, postprocess_.textureColorBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 6);
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
	GLuint projLoc = glGetUniformLocation(ShaderProgram, "Projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);
	GLuint viewLoc = glGetUniformLocation(ShaderProgram, "View");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
	GLuint worldLoc = glGetUniformLocation(ShaderProgram, "World");
	glUniformMatrix4fv(worldLoc, 1, GL_FALSE, &Trans->World[0][0]);

	glm::mat3 normalMat = glm::transpose(glm::inverse(Trans->World));
	GLuint normalMatLoc = glGetUniformLocation(ShaderProgram, "NormalMatrix");
	glUniformMatrix3fv(normalMatLoc, 1, GL_TRUE, &normalMat[0][0]);

	GLuint viewPosLoc = glGetUniformLocation(ShaderProgram, "ViewPos");
	glUniform3f(viewPosLoc, eye.x, eye.y, eye.z);
}

void Engine::GraphicSystem::RenderMesh(unsigned int VAOIndex, int ShaderProgram, unsigned int TextureIndex, unsigned int NoIndices) {
	glUseProgram(ShaderProgram);
	int loc = glGetUniformLocation(ShaderProgram, "hdrToggle");
	glUniform1f(loc, postprocess_.hdrToggle);
	glBindVertexArray(VAOIndex);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureIndex);
	glDrawElements(GL_TRIANGLES, NoIndices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Engine::GraphicSystem::SetDirectionalLight(int ShaderProgram, DirectionalLight* Light) {
	if (!Light->bIsDirty)
		return;

	GLuint dirLoc = glGetUniformLocation(ShaderProgram, "DirLight.Direction");
	glUniform3f(dirLoc, Light->Direction.x, Light->Direction.y, Light->Direction.z);
	GLuint colorLoc = glGetUniformLocation(ShaderProgram, "DirLight.Color");
	glUniform3f(colorLoc, Light->Color.x, Light->Color.y, Light->Color.z);
	GLuint intensityLoc = glGetUniformLocation(ShaderProgram, "DirLight.Intensity");
	glUniform1f(intensityLoc, Light->Intensity);

	//Light->bIsDirty = false;
}

void Engine::GraphicSystem::SetPointLight(int ShaderProgram, PointLight* Light, int Index) {
	if (!Light->bIsDirty)
		return;

	Transform* trans = Light->AssignedTo->Get<Transform>().Get();
	std::string indexed = "PointLights[";
	indexed += std::to_string(Index).c_str();

	GLuint posLoc = glGetUniformLocation(ShaderProgram, (indexed + "].Position").c_str());
	glUniform3f(posLoc, trans->Position.x, trans->Position.y, trans->Position.z);
	GLuint colorLoc = glGetUniformLocation(ShaderProgram, (indexed + "].Color").c_str());
	glUniform3f(colorLoc, Light->Color.x, Light->Color.y, Light->Color.z);
	GLuint intensityLoc = glGetUniformLocation(ShaderProgram, (indexed + "].Intensity").c_str());
	glUniform1f(intensityLoc, Light->Intensity);
	GLuint constantLoc = glGetUniformLocation(ShaderProgram, (indexed + "].Constant").c_str());
	glUniform1f(constantLoc, Light->Constant);
	GLuint lineraLoc = glGetUniformLocation(ShaderProgram, (indexed + "].Linear").c_str());
	glUniform1f(lineraLoc, Light->Linear);
	GLuint quadraticLoc = glGetUniformLocation(ShaderProgram, (indexed + "].Quadratic").c_str());
	glUniform1f(quadraticLoc, Light->Quadratic);

	//Light->bIsDirty = false;
}

void Engine::GraphicSystem::SetSpotLight(int ShaderProgram, SpotLight* Light) {
	Transform* trans = Light->AssignedTo->Get<Transform>().Get();

	GLuint dirLoc = glGetUniformLocation(ShaderProgram, "Spot.Direction");
	glUniform3f(dirLoc, Light->Direction.x, Light->Direction.y, Light->Direction.z);
	GLuint posLoc = glGetUniformLocation(ShaderProgram, "Spot.Position");
	glUniform3f(posLoc, trans->Position.x, trans->Position.y, trans->Position.z);
	GLuint colorLoc = glGetUniformLocation(ShaderProgram, "Spot.Color");
	glUniform3f(colorLoc, Light->Color.x, Light->Color.y, Light->Color.z);
	GLuint intensityLoc = glGetUniformLocation(ShaderProgram, "Spot.Intensity");
	glUniform1f(intensityLoc, Light->Intensity);

	GLuint cutoffLoc = glGetUniformLocation(ShaderProgram, "Spot.Cutoff");
	glUniform1f(cutoffLoc, Light->Cutoff);
	GLuint outerLoc = glGetUniformLocation(ShaderProgram, "Spot.OuterCutoff");
	glUniform1f(outerLoc, Light->OuterCutoff);
}

void Engine::GraphicSystem::DrawBackground(Engine::Color BckColor) {
	glClearColor(BckColor.R, BckColor.G, BckColor.B, BckColor.A);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::GraphicSystem::FinalizeRender() {
	glfwSwapBuffers(glfwGetCurrentContext());
}

void Engine::GraphicSystem::DrawSkybox() {
	//glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);
	glUseProgram(skybox_.shaderIndex);

	//View matrix
	Camera* camera = SceneManager::GetCurrent()->MainCamera.Get()->Get<Camera>().Get();
	Transform* cameraTransform = SceneManager::GetCurrent()->MainCamera.Get()->Get<Transform>().Get();
	glm::vec3 eye = cameraTransform->Position;
	glm::vec3 dir = glm::normalize(cameraTransform->Forward);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::lookAt(eye, eye + dir, up);
	view = glm::mat4(glm::mat3(view));

	//Projection matrix
	int w, h;
	glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);
	glm::mat4 projection = glm::perspective(45.0f, (float)w / (float)h, 0.001f, 50.0f);

	//WVP matrix
	GLuint projLoc = glGetUniformLocation(skybox_.shaderIndex, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);
	GLuint viewLoc = glGetUniformLocation(skybox_.shaderIndex, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

	glBindVertexArray(skybox_.vaoIndex_);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_.textureId_);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//glDepthMask(GL_TRUE);
}