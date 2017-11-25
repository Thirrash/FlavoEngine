#pragma once

#include <EntityX.h>
#include <map>
#include "SceneObjectHandle.h"
#include <OpenGL/assimp/scene.h>
#include "Camera.h"

namespace Engine
{
	class Transform;

	class Scene : public EntityX
	{
		/*** Constants ***/
		/*** Ctors ***/
	public:
		Scene();
		~Scene();

		/*** Fields ***/
	public:
		SceneObjectHandle MainCamera;

	private:
		std::map<Entity::Id, SceneObjectHandle> Objects;

		/*** Methods ***/
	public:
		SceneObjectHandle Instantiate();
		SceneObjectHandle Instantiate(std::string ModelPath);
		bool Destroy(SceneObjectHandle Object);
		EventManager& GetEventManager();
		void ChangeParent(ComponentHandle<Transform> Parent, ComponentHandle<Transform> Child);

	private:
		void ProcessModelNode(aiNode* Node, const aiScene* AiScene, SceneObjectHandle& RootObject, SceneObjectHandle& Parent, std::string Directory);
	};
}