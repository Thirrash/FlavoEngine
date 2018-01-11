#pragma once

class GLFWwindow;
class Postprocess
{
public:
	Postprocess();

	void OnZkey();

public:
	unsigned int framebuffer;
	unsigned int textureColorBuffer;
	unsigned int shaderProgram;
	unsigned int vaoIndex;
	float hdrToggle;

private:
	bool lastPressed_;
};