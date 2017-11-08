#pragma once

#include "EntityX.h"

namespace Engine
{
	class SceneObject;

	/**
	 * A SceneObjectHandle is a wrapper around an instance of a SceneObject.
	 * It provides safe access to SceneObject, with nullptr detection.
	 */
	class SceneObjectHandle
	{
		/*** Constants ***/
		/*** Ctors ***/
	public:
		SceneObjectHandle();
		SceneObjectHandle(EntityManager* Manager, SceneObject* Object);
		~SceneObjectHandle();

		/*** Fields ***/
	private:
		EntityManager* Manager;
		SceneObject* Object;
		Entity Id;

		/*** Methods ***/
	public:
		SceneObject* Get();
		bool IsValid();
		void Destroy();
	};
}