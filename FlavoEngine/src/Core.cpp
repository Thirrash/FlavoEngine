#include "Core.h"
#include <time.h>
#include <iostream>
#include "Debug.h"
#include "Framework/FWindow.h"
#include "Framework/FUtils.h"
#include "SceneManager.h"
#include "Scene.h"
#include "SceneObjectHandle.h"
#include "SceneObject.h"
#include "Transform.h"
#include "Systems/GraphicSystem.h"
#include "Systems/UserSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/TransformSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/GUISystem.h"
#include "Color.h"

using namespace Framework;

Engine::Core::Core() {
	MainWindow = new FWindow();
	MainWindow->Initi();
	::GLFWwindow* window = MainWindow->GlfwWindow;
}

Engine::Core::~Core() {
	delete MainWindow;
}

int Engine::Core::StartGame() {
	LogA("Started Game");
	CurrentTime = FUtils::GetTime();

	Scene* currentScene = SceneManager::GetCurrent();
	GraphicSystem graphicSystem;
	SystemUpdate<GUISystem> guiSystem(new GUISystem(), 0.0);
	SystemUpdate<UserSystem> userSystem(new UserSystem(currentScene->entities), 1.0 / MAX_FRAMERATE);
	SystemUpdate<InputSystem> inputSystem(new InputSystem(), 1.0 / MAX_FRAMERATE);
	SystemUpdate<TransformSystem> transformSystem(new TransformSystem(), 1.0 / MAX_FRAMERATE);
	SystemUpdate<CollisionSystem> collisionSystem(new CollisionSystem(), 1.0 / MAX_FRAMERATE);

	graphicSystem.configure(currentScene->GetEventManager());

	int count = 0;
	while (!FUtils::CheckGameLoopClose()) {
		double newTime = FUtils::GetTime();
		double deltaTime = newTime - CurrentTime;
		FUtils::PollEvents();

		currentScene = SceneManager::GetCurrent();
		if (currentScene == nullptr) {
			LogR("Exited: scene is null");
			return 1;
		}

		graphicSystem.DrawBackground(Color(0.2f, 0.3f, 0.4f, 1.0f));

		inputSystem.Update(currentScene->entities, currentScene->events, deltaTime);
		userSystem.Update(currentScene->entities, currentScene->events, deltaTime);
		transformSystem.Update(currentScene->entities, currentScene->events, deltaTime);
		collisionSystem.Update(currentScene->entities, currentScene->events, deltaTime);
		graphicSystem.Update(currentScene->entities, currentScene->events, deltaTime);
		guiSystem.Update(currentScene->entities, currentScene->events, deltaTime);
		
		graphicSystem.FinalizeRender();
		CurrentTime = newTime;
	}

	FUtils::Terminate();
	return 0;
}

