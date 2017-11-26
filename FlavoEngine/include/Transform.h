#pragma once

#include "InternalComponent.h"
#include <EntityX.h>
#include <map>
#include "Vector3.h"
#include "OpenGL/glm/glm.hpp"
#include "OpenGL/glm/gtc/quaternion.hpp"

namespace Engine
{
	enum TransformDirtiness
	{
		NoChange,
		AppliedTransform,
		PendingApply
	};

	class Transform : public InternalComponent<Transform>
	{
		/*** Constants ***/
		/*** Ctors ***/
	public:
		Transform();
		virtual ~Transform();

		/*** Fields ***/
	public:
		glm::vec3 Position;
		glm::vec3 LocalPosition;

		glm::quat Rotation;
		glm::quat LocalRotation;

		glm::vec3 Scale;
		glm::vec3 LocalScale;

		ComponentHandle<Transform> Parent;
		std::map<Entity, ComponentHandle<Transform>> Children;

		glm::vec3 Forward;
		glm::vec3 Right;
		glm::vec3 Up;

		glm::mat4x4 World;
		glm::mat4x4 LocalWorld;

		TransformDirtiness Dirtiness;
		bool bHasParentChanged;

		/*** Methods ***/
	public:
		void SetLocalPosition(glm::vec3 Pos);
		void SetLocalRotation(glm::quat Rot);
		void SetLocalScale(glm::vec3 Scale);
	};
}