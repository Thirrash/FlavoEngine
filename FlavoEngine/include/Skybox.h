#pragma once

#include <string>
#include <vector>

class Skybox
{
public:
	Skybox();
	unsigned int LoadCubemap(std::vector<std::string> TexturePaths);

	unsigned int shaderIndex;
	unsigned int textureId_;
	unsigned int vaoIndex_;

private:
	void InitBuffers();
};