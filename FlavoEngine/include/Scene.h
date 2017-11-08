#pragma once

#include <EntityX.h>
#include <map>
#include "SceneObjectHandle.h"
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
		bool Destroy(SceneObjectHandle Object);
		EventManager& GetEventManager();
		void ChangeParent(ComponentHandle<Transform> Parent, ComponentHandle<Transform> Child);
	};
}