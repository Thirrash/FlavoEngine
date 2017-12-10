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
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include <cmath>
#include "Camera.h"
#include <GLFW/glfw3.h>

CubeSpawner::CubeSpawner() : LastInput(0.0f, 0.0f, 0.0f) {

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

SceneObjectHandle CubeSpawner::CreatePointLight(glm::vec3 pos, glm::vec3 color, float intensity, std::string texturePath) {
	SceneObjectHandle obj = SceneManager::GetCurrent()->Instantiate("../../Resources/Models/Cube.FBX");
	ComponentHandle<Transform> trans = obj.Get()->Get<Transform>();
	trans.Get()->SetLocalPosition(pos);
	trans.Get()->SetLocalScale(trans.Get()->LocalScale);

	ComponentHandle<PointLight> point = obj.Get()->Add<PointLight>();
	point.Get()->SetColor(color);
	point.Get()->SetIntensity(intensity);

	return obj;
}

void CubeSpawner::Start() {
	StartTime = Framework::FUtils::GetTime();

	//Camera
	Transform* cameraTransform = SceneManager::GetCurrent()->MainCamera.Get()->Get<Transform>().Get();
	cameraTransform->SetLocalPosition(glm::vec3(0.0f, 0.0f, -10.0f));
	cameraTransform->SetLocalRotation(glm::quat(glm::vec3(0.0f, 0.0, 0.0f)));

	//DirLight
	SceneObjectHandle dirLightObj = SceneManager::GetCurrent()->Instantiate();
	ComponentHandle<DirectionalLight> dirLight = dirLightObj.Get()->Add<DirectionalLight>();
	dirLight.Get()->Direction = glm::vec3(0.0f, -1.0f, 0.0f);
	Dir = dirLightObj;

	//PointLights
	SceneObjectHandle point0 = CreatePointLight(glm::vec3(0.32f, 2.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 1.1f, "../../Resources/Images/brick.jpg");
	SceneObjectHandle point1 = CreatePointLight(glm::vec3(4.0f, 4.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.01f, "../../Resources/Images/brick.jpg");
	SceneObjectHandle point2 = CreatePointLight(glm::vec3(0.0f, 4.0f, 4.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0.01f, "../../Resources/Images/brick.jpg");
	SceneObjectHandle point3 = CreatePointLight(glm::vec3(4.0f, 0.0f, 4.0f), glm::vec3(1.0f, 0.0f, 1.0f), 0.01f, "../../Resources/Images/brick.jpg");
	Point.push_back(point0);
	Point.push_back(point1);
	Point.push_back(point2);
	Point.push_back(point3);

	//SpotLight
	SceneObjectHandle spotLightObj = SceneManager::GetCurrent()->Instantiate("../../Resources/Models/Cube.FBX");
	ComponentHandle<SpotLight> spotLight = spotLightObj.Get()->Add<SpotLight>();
	spotLight.Get()->SetParams(glm::vec3(0.0f, 1.0f, 0.0f), glm::cos(glm::radians(6.5f)), glm::cos(glm::radians(10.5f)));
	spotLight.Get()->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
	spotLight.Get()->SetIntensity(1.0f);

	Transform* spotTrans = spotLightObj.Get()->Get<Transform>().Get();
	spotTrans->SetLocalPosition(glm::vec3(0.0f, -1.0f, 0.0f));
	Spot = spotLightObj;

	SceneObjectHandle imported = SceneManager::GetCurrent()->Instantiate("../../Resources/Models/Totem.FBX");
	//Material& mat = imported.Get()->Get<MeshRenderer>().Get()->CurrentMat;
	//mat.ChangeProperties(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), 100.0f);
}

void CubeSpawner::Update(double DeltaTime) {
	float currentTime = Framework::FUtils::GetTime() - StartTime;
	float trueDelta = (currentTime - StartTime);

	Point[0].Get()->Get<Transform>().Get()->SetLocalPosition(glm::vec3(glm::sin(trueDelta) * 0.32f, 2.0f, glm::cos(trueDelta) * 0.32f));
	Point[0].Get()->Get<PointLight>().Get()->SetColor(glm::vec3(glm::sin(trueDelta * 0.4f), 0.0f, glm::cos(trueDelta * 0.4f)));
	Point[0].Get()->Get<PointLight>().Get()->SetIntensity(glm::sin(trueDelta) + 2.0f);

	Transform* cameraTransform = SceneManager::GetCurrent()->MainCamera.Get()->Get<Transform>().Get();
	float cameraSpeed = 4.0f * DeltaTime;
	cameraTransform->SetLocalPosition(cameraTransform->LocalPosition + cameraSpeed * ((cameraTransform->Forward * (float)(Input::IsKeyDown(EKeyCode::W) - Input::IsKeyDown(EKeyCode::S))) + cameraTransform->Right * (float)(Input::IsKeyDown(EKeyCode::D) - Input::IsKeyDown(EKeyCode::A)) + cameraTransform->Up * (float)(Input::IsKeyDown(EKeyCode::Q) - Input::IsKeyDown(EKeyCode::E))));
}