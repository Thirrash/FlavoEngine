#include "Core.h"
#include <string>
#include "SceneManager.h"
#include "SceneObjectHandle.h"
#include "SceneObject.h"
#include "EntityX.h"
#include "Scene.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "CubeSpawner.h"

using namespace Engine;

int main() {
	Core core;
	SceneManager::LoadScene("[pH]");
	SceneObjectHandle spawnManager = SceneManager::GetCurrent()->Instantiate();
	spawnManager.Get()->Add<CubeSpawner>().Get()->configure(SceneManager::GetCurrent()->GetEventManager());

	return core.StartGame();
}