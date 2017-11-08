#pragma once
#include <string>

#define STB_IMAGE_IMPLEMENTATION

using namespace std;

namespace Framework
{
	class FUtils
	{
		/*** Constants ***/
		/*** Ctors ***/
	private:
		FUtils();

		/*** Fields ***/
		/*** Methods ***/
	private:
		static string LoadShaderFromFile(string Path);
		static bool CheckShaderCompilation(int ShaderIndex, string ShaderType);

	public:
		static double GetTime();
		static bool CheckGameLoopClose();
		static void PollEvents();
		static void Terminate();

		static int CompileShader(string VertexPath, string FragmentPath);
		static unsigned char* LoadTextureFromFile(string Path, int* Width, int* Height, int* NoChannels);
		static void DeallocateTextureFile(unsigned char* Data);
	};
}
