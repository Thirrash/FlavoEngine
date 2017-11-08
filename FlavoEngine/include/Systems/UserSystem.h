#pragma once

#include <EntityX.h>

namespace Engine
{
	class UserSystem : public System<UserSystem>
	{
		/*** Constants ***/
		/*** Ctors ***/
	public:
		UserSystem(EntityManager& es);
		~UserSystem();

		/*** Fields ***/
		/*** Methods ***/
	public:
		void Update(EntityManager& es, EventManager& events, TimeDelta dt) override;
	};
}