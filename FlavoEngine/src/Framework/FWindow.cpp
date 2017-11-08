#include "FWindow.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Debug.h"

Framework::FWindow::FWindow() {}

Framework::FWindow::~FWindow() {
	delete GlfwWindow;
}

Framework::EWindowInitErrorCode Framework::FWindow::Initi() {
	if (!glfwInit()) {
		LogR("Failed to init GLFW");
		return GlfwInitError;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GlfwWindow = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "PAG Ex2", NULL, NULL);
	if (!GlfwWindow) {
		LogR("Failed to create GLFW window");
		glfwTerminate();
		return GlfwWindowNull;
	}

	glfwMakeContextCurrent(GlfwWindow);

	//glfw uses C-style pointers and we need to somehow assign method pointer to it
	glfwSetWindowUserPointer(GlfwWindow, this);
	glfwSetFramebufferSizeCallback(GlfwWindow, [](GLFWwindow* Window, int Width, int Height) {static_cast<FWindow*>(glfwGetWindowUserPointer(Window))->OnFramebufferSizeChange(Window, Width, Height); });

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		LogR("Failed to load GLAD");
		return GladInitError;
	}

	return Success;
}

void Framework::FWindow::Close() {
	glfwSetWindowShouldClose(GlfwWindow, true);
}

void Framework::FWindow::OnFramebufferSizeChange(GLFWwindow* Window, int Width, int Height) {
	glViewport(0, 0, Width, Height);
}