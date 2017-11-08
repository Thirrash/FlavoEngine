#pragma once

#include "EntityX.h"

namespace Engine
{
	class SceneObject;

	class UserComponent : public Component<UserComponent>
	{
		/*** Constants ***/
		/*** Ctors ***/
	protected:
		UserComponent() {}
		virtual ~UserComponent() {}

		/*** Fields ***/
	public:
		SceneObject* AssignedTo;

		/*** Methods ***/
	public:
		virtual void Start() {}
		virtual void Update(double DeltaTime) {}

		/* Internal use only */
		static Family family();
	};
}