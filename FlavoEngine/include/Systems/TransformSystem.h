#pragma once

#include "EntityX.h"
#include <map>
#include <OpenGL/glm/glm.hpp>

namespace Engine
{
	class Transform;

	class TransformSystem : System<TransformSystem>
	{
		/*** Constants ***/
		/*** Ctors ***/
	public:
		TransformSystem();
		~TransformSystem();

		/*** Fields ***/
	private:
		std::map<Entity, ComponentHandle<Transform>> RootTransforms;

		/*** Methods ***/
	public:
		void Update(EntityManager& es, EventManager& events, TimeDelta dt) override;

	private:
		void ChangeWorld(ComponentHandle<Transform> TransHandle, bool bIsParentDirty);
	};
}