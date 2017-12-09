#include "Systems\GUISystem.h"
#include "../src/ImGui/imgui_impl_glfw_gl3.cpp"
#include "Camera.h"
#include "SceneManager.h"
#include "Scene.h"
#include "SceneObject.h"
#include "Collider.h"
#include "Systems/CollisionSystem.h"
#include "Debug.h"
#include "Transform.h"

Engine::GUISystem::GUISystem() {
	ImGui_ImplGlfwGL3_Init(glfwGetCurrentContext(), true);
}

Engine::GUISystem::~GUISystem() {
	ImGui_ImplGlfwGL3_Shutdown();
}

void Engine::GUISystem::Update(EntityManager& es, EventManager& events, TimeDelta dt) {
	ImGui_ImplGlfwGL3_NewFrame();
	static ComponentHandle<Collider> lastHit;

	Camera* cam = SceneManager::GetCurrent()->MainCamera.Get()->Get<Camera>().Get();
	Ray cameraRay = cam->GetRayFromMousePosition(20.0f);
	ComponentHandle<Collider> hit;
	glm::vec3 hitPoint;
	if (CollisionSystem::Raycast(cameraRay.Origin, cameraRay.End, hit, hitPoint)) {
		//LogB(hit.Get()->AssignedTo->Name, hitPoint.x, hitPoint.y, hitPoint.z, hit.Get()->AssignedTo->Get<Transform>().Get()->Position.x, hit.Get()->AssignedTo->Get<Transform>().Get()->Position.y, hit.Get()->AssignedTo->Get<Transform>().Get()->Position.z);
	}

	if (hit.IsDefault()) {
		hit = lastHit;
	} else {
		lastHit = hit;
	}

	if (hit.IsValid()) {
		Transform* trans = hit.Get()->AssignedTo->Get<Transform>().Get();
		float posX = trans->LocalPosition.x, posY = trans->LocalPosition.y, posZ = trans->LocalPosition.z;
		glm::vec3 rot = glm::degrees(glm::eulerAngles(trans->LocalRotation));
		float rotX = rot.x, rotY = rot.y, rotZ = rot.z;
		float scaleX = trans->LocalScale.x, scaleY = trans->LocalScale.y, scaleZ = trans->LocalScale.z;

		ImGui::SetNextWindowSize(ImVec2(200.0f, 400.0f));
		ImGui::Begin("Inspector");
		ImGui::LabelText("Name", hit.Get()->AssignedTo->Name.c_str());

		ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Position:");
		ImGui::InputFloat("pX", &posX, 0.01f, 0.0f, 2);
		ImGui::InputFloat("pY", &posY, 0.01f, 0.0f, 2);
		ImGui::InputFloat("pZ", &posZ, 0.01f, 0.0f, 2);

		ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Rotation:");
		ImGui::InputFloat("rX", &rotX, 0.0f, 0.0f, 2);
		ImGui::InputFloat("rY", &rotY, 0.0f, 0.0f, 2);
		ImGui::InputFloat("rZ", &rotZ, 0.0f, 0.0f, 2);

		ImGui::TextColored(ImVec4(0.0f, 0.0f, 1.0f, 1.0f), "Scale:");
		ImGui::InputFloat("sX", &scaleX, 0.02f, 0.0f, 2);
		ImGui::InputFloat("sY", &scaleY, 0.02f, 0.0f, 2);
		ImGui::InputFloat("sZ", &scaleZ, 0.02f, 0.0f, 2);
		ImGui::End();

		if (posX != trans->LocalPosition.x || posY != trans->LocalPosition.y || posZ != trans->LocalPosition.z)
			trans->SetLocalPosition(glm::vec3(posX, posY, posZ));

		if (rotX != rot.x || rotY != rot.y || rotZ != rot.z)
			trans->SetLocalRotation(glm::quat(glm::radians(glm::vec3(rotX, rotY, rotZ))));

		if (scaleX != trans->LocalScale.x || scaleY != trans->LocalScale.y || scaleZ != trans->LocalScale.z)
			trans->SetLocalScale(glm::vec3(scaleX, scaleY, scaleZ));
	}




	ImGui::Render();
}
