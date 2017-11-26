#pragma once

#include <vector>
#include <EntityX.h>
#include <string>

namespace Engine
{
	class Transform;
	class SceneObject
	{
		/*** Constants ***/
		/*** Ctors ***/
	public:
		SceneObject(Entity Id);
		~SceneObject();

		/*** Fields ***/
	public:
		Entity Id;
		std::string Name;

	private:
		ComponentHandle<Transform> Trans;

		/*** Methods ***/
	public:
		template<typename T> ComponentHandle<T> Add() {
			ComponentHandle<T> handle = Id.assign<T>();
			handle.Get()->AssignedTo = this;
			return handle;
		}

		template<typename T> ComponentHandle<T> Get() {
			return Id.component<T>();
		}

		template<typename T> void Remove() {
			Id.remove<T>();
		}

		bool IsNull();
	};
}