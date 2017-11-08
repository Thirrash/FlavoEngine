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
	Vertices = new float[64] {
		//pos					//color					//UV coords
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
		1.0f, -1.0f, -1.0f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
		1.0f, 1.0f, -1.0f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
		1.0f, -1.0f, 1.0f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f,
		-1.0f, -1.0f, 1.0f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f
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
	cameraTransform->SetLocalRotation(cameraTransform->LocalRotation + Vector3(Input.Y * 0.01, Input.X * 0.01, 0.0f));
}

void CubeSpawner::Start() {
	SceneObjectHandle cube1 = CreateCube(Vector3(12.0, 0.0, 0.0), "../../Resources/Images/brick.jpg");
	cube1.Get()->Get<Transform>().Get()->SetLocalScale(Vector3(0.2f, 0.2f, 0.2f));
	Cubes.push_back(cube1);

	SceneObjectHandle cube2 = CreateCube(Vector3(2.0, 0.0, 0.0), "../../Resources/Images/brick.jpg");
	cube2.Get()->Get<Transform>().Get()->SetLocalRotation(Vector3(0.0f, 45.0f * 0.0174533f, 0.0f));
	Cubes.push_back(cube2);

	SceneManager::GetCurrent()->ChangeParent(cube2.Get()->Get<Transform>(), cube1.Get()->Get<Transform>());

	Transform* cameraTransform = SceneManager::GetCurrent()->MainCamera.Get()->Get<Transform>().Get();
	cameraTransform->SetLocalPosition(Vector3(0.0f, 10.0f, 0.0f));
	cameraTransform->SetLocalRotation(Vector3(-95.0f, 0.0, 0.0f));

	StartTime = Framework::FUtils::GetTime();
}

void CubeSpawner::Update(double DeltaTime) {
	float currentTime = Framework::FUtils::GetTime() - StartTime;
	float trueDelta = (currentTime - StartTime);
	Cubes[1].Get()->Get<Transform>().Get()->SetLocalPosition(Vector3(cos(trueDelta), 0.0, sin(trueDelta)) * 2.0);
	Cubes[0].Get()->Get<Transform>().Get()->SetLocalPosition(Vector3(sin(trueDelta), 0.0, cos(trueDelta)) * 12.0);
	LogB(Cubes[0].Get()->Get<Transform>().Get()->World[3][0]);

	Transform* cameraTransform = SceneManager::GetCurrent()->MainCamera.Get()->Get<Transform>().Get();
	if (Input::IsKeyDown(EKeyCode::W)) {
		cameraTransform->SetLocalPosition(cameraTransform->LocalPosition + cameraTransform->Forward * 0.1f);
	}

	if (Input::IsKeyDown(EKeyCode::A)) {
		cameraTransform->SetLocalPosition(cameraTransform->LocalPosition - cameraTransform->Right * 0.1f);
	}

	if (Input::IsKeyDown(EKeyCode::S)) {
		cameraTransform->SetLocalPosition(cameraTransform->LocalPosition - cameraTransform->Forward * 0.1f);
	}

	if (Input::IsKeyDown(EKeyCode::D)) {
		cameraTransform->SetLocalPosition(cameraTransform->LocalPosition + cameraTransform->Right * 0.1f);
	}
}

SceneObjectHandle CubeSpawner::CreateCube(Vector3 pos, std::string texturePath) {
	SceneObjectHandle obj = SceneManager::GetCurrent()->Instantiate();
	ComponentHandle<Transform> trans = obj.Get()->Get<Transform>();
	trans.Get()->SetLocalPosition(pos);

	Mesh mesh(Vertices, 8 * 8, Indices, 6 * 6);
	ComponentHandle<MeshRenderer> renderer = obj.Get()->Add<MeshRenderer>();
	renderer.Get()->AssignMesh(mesh);
	renderer.Get()->AssignTexture(texturePath);

	return obj;
}