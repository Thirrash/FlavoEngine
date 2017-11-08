#include "SceneManager.h"
#include "Scene.h"

Engine::Scene* Engine::SceneManager::CurrentScene = nullptr;

void Engine::SceneManager::LoadScene(std::string Path) {
	//[pH] requires actual scene laoding from file
	Scene* loadedScene = new Scene();
	CurrentScene = loadedScene;
}

Engine::Scene* Engine::SceneManager::GetCurrent() {
	return CurrentScene;
}
