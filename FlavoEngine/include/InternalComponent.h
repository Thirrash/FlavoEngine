#pragma once

#include "EntityX.h"

namespace Engine
{
	class SceneObject;

	template <typename T>
	class InternalComponent : public Component<T>
	{
		/*** Constants ***/
		/*** Ctors ***/
	protected:
		virtual ~InternalComponent();

		/*** Fields ***/
	public:
		SceneObject* AssignedTo;

		/*** Methods ***/
	public:
		static Family family() {
			static Family family = family_counter_++;
			assert(family < Engine::MAX_COMPONENTS - 1);
			return family;
		}
	};

	template<typename T>
	inline InternalComponent<T>::~InternalComponent() {}
}