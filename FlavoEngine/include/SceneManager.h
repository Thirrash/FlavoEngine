#pragma once

#include <string>

namespace Engine
{
	class Scene;
	class SceneManager
	{
		/*** Constants ***/
		/*** Ctors ***/
	private:
		SceneManager();

		/*** Fields ***/
	private:
		static Scene* CurrentScene;

		/*** Methods ***/
	public:
		static void LoadScene(std::string Path);
		static Scene* GetCurrent();
	};
}