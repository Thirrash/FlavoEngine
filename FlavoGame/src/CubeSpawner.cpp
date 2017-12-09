#include "CubeSpawner.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Transform.h"
#include "SceneObject.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Debug.h"
#include "Framework/FUtils.h"
#include "SphereCollider.h"
#include "Systems/CollisionSystem.h"
#include <cmath>
#include "Camera.h"
#include <GLFW/glfw3.h>

CubeSpawner::CubeSpawner() : LastInput(0.0f, 0.0f, 0.0f) {
	Vertices = new float[40] {
		//pos					//UV coords
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f,
		1.0f, -1.0f, -1.0f,		1.0f, 0.0f,
		1.0f, 1.0f, -1.0f,		1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,		0.0f, 1.0f,
		1.0f, -1.0f, 1.0f,		0.0f, 0.0f,
		-1.0f, -1.0f, 1.0f,		0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,		0.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,		1.0f, 1.0f
	};

	Indices = new unsigned int[36] {
		3, 0, 1,		3, 1, 2,
		2, 1, 4,		2, 4, 6,
		7, 5, 0,		7, 0, 3,
		6, 4, 5,		6, 5, 7,
		7, 3, 2,		7, 2, 6,
		5, 0, 1,		5, 1, 4
	};
}

void CubeSpawner::configure(EventManager& event_manager) {
	event_manager.subscribe<MouseInput>(*this);
}

void CubeSpawner::receive(const MouseInput& Input) {
	if (glfwGetInputMode(glfwGetCurrentContext(), GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
		return;

	Transform* cameraTransform = SceneManager::GetCurrent()->MainCamera.Get()->Get<Transform>().Get();
	glm::quat newRotation = cameraTransform->LocalRotation * glm::quat(glm::vec3((Input.Y - LastInput.Y) * 0.001, 0.0f, 0.0f)); //local x-axis rotation
	newRotation = glm::quat(glm::vec3(0.0f, -(Input.X - LastInput.X) * 0.001, 0.0f)) * newRotation;
	cameraTransform->SetLocalRotation(newRotation);
	LastInput = Input;
}

void CubeSpawner::Start() {
	Transform* cameraTransform = SceneManager::GetCurrent()->MainCamera.Get()->Get<Transform>().Get();
	cameraTransform->SetLocalPosition(glm::vec3(0.0f, 0.0f, -10.0f));
	cameraTransform->SetLocalRotation(glm::quat(glm::vec3(0.0f, 0.0, 0.0f)));

	StartTime = Framework::FUtils::GetTime();

	SceneObjectHandle imported = SceneManager::GetCurrent()->Instantiate("../../Resources/Models/Totem.FBX");
	//imported.Get()->Get<Transform>().Get()->SetLocalPosition(glm::vec3(5.0f, 0.0f, 0.0f));
}

void CubeSpawner::Update(double DeltaTime) {
	float currentTime = Framework::FUtils::GetTime() - StartTime;
	float trueDelta = (currentTime - StartTime);

	Transform* cameraTransform = SceneManager::GetCurrent()->MainCamera.Get()->Get<Transform>().Get();
	float cameraSpeed = 4.0f * DeltaTime;
	cameraTransform->SetLocalPosition(cameraTransform->LocalPosition + cameraSpeed * ((cameraTransform->Forward * (float)(Input::IsKeyDown(EKeyCode::W) - Input::IsKeyDown(EKeyCode::S))) + cameraTransform->Right * (float)(Input::IsKeyDown(EKeyCode::D) - Input::IsKeyDown(EKeyCode::A)) + cameraTransform->Up * (float)(Input::IsKeyDown(EKeyCode::Q) - Input::IsKeyDown(EKeyCode::E))));
}

SceneObjectHandle CubeSpawner::CreateCube(glm::vec3 pos, std::string texturePath) {
	SceneObjectHandle obj = SceneManager::GetCurrent()->Instantiate();
	ComponentHandle<Transform> trans = obj.Get()->Get<Transform>();
	trans.Get()->SetLocalPosition(pos);

	Mesh mesh(Vertices, 8 * 5, Indices, 6 * 6);
	ComponentHandle<MeshRenderer> renderer = obj.Get()->Add<MeshRenderer>();
	renderer.Get()->AssignMesh(mesh);
	renderer.Get()->CurrentMat.AssignTexture(texturePath);

	ComponentHandle<SphereCollider> collider = obj.Get()->Add<SphereCollider>();
	collider.Get()->SetRadius(1.0f);

	return obj;
}