#pragma once

class GLFWwindow;

namespace Framework
{
	enum EWindowInitErrorCode
	{
		Success,
		GlfwInitError,
		GlfwWindowNull,
		GladInitError
	};

	class FWindow
	{
		/*** Constants ***/
	private:
		const int DEFAULT_WIDTH = 1200;
		const int DEFAULT_HEIGHT = 800;

		/*** Ctors ***/
	public:
		FWindow();
		~FWindow();

		/*** Fields ***/
	public:
		GLFWwindow* GlfwWindow;

		/*** Methods ***/
	public:
		EWindowInitErrorCode Initi();
		void Close();

	private:
		void OnFramebufferSizeChange(GLFWwindow* Window, int Width, int Height);
	};
}
