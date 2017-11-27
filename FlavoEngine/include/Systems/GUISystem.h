#pragma once

#include "EntityX.h"

namespace Engine
{
	class Transform;
	class Color;

	class GUISystem : public System<GUISystem>
	{
		/*** Constants ***/
		/*** Ctors ***/
	public:
		GUISystem();
		~GUISystem();

		/*** Fields ***/

		/*** Methods ***/
	public:
		void Update(EntityManager& es, EventManager& events, TimeDelta dt) override;
	};
}