#pragma once
#include <string>

namespace Engine {
	class Color; 
	class Mesh;
	class Transform;
}

using namespace std;

namespace Framework
{
	class FDraw
	{
		/*** Constants ***/
		/*** Ctors ***/
	private:
		FDraw();

		/*** Fields ***/
		/*** Methods ***/
	public:
		static unsigned int BindVAO(Engine::Mesh& Data);
		static unsigned int BindTexture(string Path);
	};
}
