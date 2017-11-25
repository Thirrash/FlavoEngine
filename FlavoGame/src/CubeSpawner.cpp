#include "CubeSpawner.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Transform.h"
#include "SceneObject.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Debug.h"
#include "Framework/FUtils.h"
#include <cmath>

CubeSpawner::CubeSpawner() {
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
	Transform* cameraTransform = SceneManager::GetCurrent()->MainCamera.Get()->Get<Transform>().Get();
	cameraTransform->SetLocalRotation(cameraTransform->LocalRotation * glm::quat(glm::vec3(Input.Y * 0.001, -Input.X * 0.001, 0.0f)));
}

void CubeSpawner::Start() {
	SceneObjectHandle cube1 = CreateCube(glm::vec3(12.0, 0.0, 0.0), "../../Resources/Images/brick.jpg");
	cube1.Get()->Get<Transform>().Get()->SetLocalScale(glm::vec3(0.2f, 0.2f, 0.2f));
	Cubes.push_back(cube1);

	SceneObjectHandle cube2 = CreateCube(glm::vec3(2.0, 0.0, 0.0), "../../Resources/Images/brick.jpg");
	cube2.Get()->Get<Transform>().Get()->SetLocalRotation(glm::vec3(0.0f, glm::radians(45.0f), 0.0f));
	Cubes.push_back(cube2);

	SceneManager::GetCurrent()->ChangeParent(cube2.Get()->Get<Transform>(), cube1.Get()->Get<Transform>());

	Transform* cameraTransform = SceneManager::GetCurrent()->MainCamera.Get()->Get<Transform>().Get();
	cameraTransform->SetLocalPosition(glm::vec3(0.0f, 0.0f, -10.0f));
	cameraTransform->SetLocalRotation(glm::quat(glm::vec3(0.0f, 0.0, 0.0f)));

	StartTime = Framework::FUtils::GetTime();

	SceneObjectHandle imported = SceneManager::GetCurrent()->Instantiate("model.FBX");
	imported.Get()->Get<Transform>().Get()->SetLocalPosition(glm::vec3(5.0f, 0.0f, 0.0f));
}

void CubeSpawner::Update(double DeltaTime) {
	float currentTime = Framework::FUtils::GetTime() - StartTime;
	float trueDelta = (currentTime - StartTime);
	//Cubes[1].Get()->Get<Transform>().Get()->SetLocalPosition(glm::vec3(cos(trueDelta), 0.0, sin(trueDelta)) * 2.0f);
	//Cubes[0].Get()->Get<Transform>().Get()->SetLocalPosition(glm::vec3(sin(trueDelta), 0.0, cos(trueDelta)) * 12.0f);
	Cubes[0].Get()->Get<Transform>().Get()->SetLocalRotation(Cubes[0].Get()->Get<Transform>().Get()->LocalRotation * glm::quat(glm::vec3(0.0f, 0.1f, 0.0f)));

	Transform* cameraTransform = SceneManager::GetCurrent()->MainCamera.Get()->Get<Transform>().Get();
	float cameraSpeed = 4.0f * DeltaTime;
	cameraTransform->SetLocalPosition(cameraTransform->LocalPosition + cameraSpeed * ((cameraTransform->Forward * (float)(Input::IsKeyDown(EKeyCode::W) - Input::IsKeyDown(EKeyCode::S))) + cameraTransform->Right * (float)(Input::IsKeyDown(EKeyCode::D) - Input::IsKeyDown(EKeyCode::A)) + cameraTransform->Up * (float)(Input::IsKeyDown(EKeyCode::Q) - Input::IsKeyDown(EKeyCode::E))));

	//LogB(glm::eulerAngles(cameraTransform->LocalRotation).x, glm::eulerAngles(cameraTransform->LocalRotation).y, glm::eulerAngles(cameraTransform->LocalRotation).z);
	//LogC(cameraTransform->LocalPosition.x, cameraTransform->LocalPosition.y, cameraTransform->LocalPosition.z);
}

SceneObjectHandle CubeSpawner::CreateCube(glm::vec3 pos, std::string texturePath) {
	SceneObjectHandle obj = SceneManager::GetCurrent()->Instantiate();
	ComponentHandle<Transform> trans = obj.Get()->Get<Transform>();
	trans.Get()->SetLocalPosition(pos);

	Mesh mesh(Vertices, 8 * 5, Indices, 6 * 6);
	ComponentHandle<MeshRenderer> renderer = obj.Get()->Add<MeshRenderer>();
	renderer.Get()->AssignMesh(mesh);
	renderer.Get()->AssignTexture(texturePath);

	return obj;
}