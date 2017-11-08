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

using namespace Framework;

Engine::Core::Core() {
	MainWindow = new FWindow();
	MainWindow->Initi();
}

Engine::Core::~Core() {
	delete MainWindow;
}

int Engine::Core::StartGame() {
	LogA("Started Game");
	CurrentTime = FUtils::GetTime();

	Scene* currentScene = SceneManager::GetCurrent();
	SystemUpdate<GraphicSystem> graphicSystem(new GraphicSystem(), 0.0);
	SystemUpdate<UserSystem> userSystem(new UserSystem(currentScene->entities), 1.0 / MAX_FRAMERATE);
	SystemUpdate<InputSystem> inputSystem(new InputSystem(), 1.0 / MAX_FRAMERATE);
	SystemUpdate<TransformSystem> transformSystem(new TransformSystem(), 1.0 / MAX_FRAMERATE);

	int count = 0;
	while (!FUtils::CheckGameLoopClose()) {
		double newTime = FUtils::GetTime();
		double deltaTime = newTime - CurrentTime;

		currentScene = SceneManager::GetCurrent();
		if (currentScene == nullptr) {
			LogR("Exited: scene is null");
			return 1;
		}

		inputSystem.Update(currentScene->entities, currentScene->events, deltaTime);
		userSystem.Update(currentScene->entities, currentScene->events, deltaTime);
		transformSystem.Update(currentScene->entities, currentScene->events, deltaTime);
		graphicSystem.Update(currentScene->entities, currentScene->events, deltaTime);

		CurrentTime = newTime;
		FUtils::PollEvents();
	}

	FUtils::Terminate();
	return 0;
}

