#pragma once

#include "InternalComponent.h"
#include <EntityX.h>
#include <map>
#include "Vector3.h"
#include "OpenGL/glm/glm.hpp"

namespace Engine
{
	class Transform : public InternalComponent<Transform>
	{
		/*** Constants ***/
		/*** Ctors ***/
	public:
		Transform();
		virtual ~Transform();

		/*** Fields ***/
	public:
		Vector3 Position;
		Vector3 LocalPosition;

		Vector3 Rotation;
		Vector3 LocalRotation;

		Vector3 Scale;
		Vector3 LocalScale;

		ComponentHandle<Transform> Parent;
		std::map<Entity, ComponentHandle<Transform>> Children;

		Vector3 Forward;
		Vector3 Right;

		glm::mat4x4 World;
		glm::mat4x4 LocalWorld;
		bool bIsDirty;
		bool bHasParentChanged;

		/*** Methods ***/
	public:
		void SetLocalPosition(Vector3 Pos);
		void SetLocalRotation(Vector3 Rot);
		void SetLocalScale(Vector3 Scale);
	};
}