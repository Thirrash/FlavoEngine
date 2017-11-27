#pragma once

#include "EntityX.h"

namespace Framework
{
	class FWindow;
}

namespace Engine
{
	class SceneBase;

	class Core
	{
		/*** Constants ***/
	private:
		const int MAX_FRAMERATE = 60;
		const double MIN_FRAME_TIME_MS = 1000.0 / MAX_FRAMERATE;

		/*** Ctors ***/
	public:
		Core();
		~Core();

		/*** Fields ***/
	private:
		Framework::FWindow* MainWindow;
		double CurrentTime;

		/*** Methods ***/
	public:
		int StartGame();

		/*** Inner classes **/
		template <typename T>
		class SystemUpdate
		{
		public:
			SystemUpdate(T* NewSystem, double Delta) : System(NewSystem), Delta(Delta), Timer(Delta) { }
			~SystemUpdate() {
				delete System;
			}

			void Update(EntityManager& Entity, EventManager& Event, double DeltaTime) {
				if (Timer >= Delta) {
					System->Update(Entity, Event, DeltaTime);
					Timer = 0.0;
				}
				Timer += DeltaTime;
			}

			T* Get() {
				return System;
			}

		private:
			T* System;
			double Delta;
			double Timer;
		};
	};
}

/*** Constants ***/
/*** Ctors ***/
/*** Fields ***/
/*** Methods ***/
