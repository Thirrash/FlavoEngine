#include "MeshRenderer.h"
#include "Framework/FDraw.h"
#include "Framework/FUtils.h"


Engine::MeshRenderer::MeshRenderer() {
	ShaderProgram = Framework::FUtils::CompileShader("../../Resources/Shaders/DefaultShader.vert", "../../Resources/Shaders/DefaultShader.frag");
}

Engine::MeshRenderer::~MeshRenderer() {

}

void Engine::MeshRenderer::AssignMesh(Mesh NewMesh) {
	CurrentMesh = NewMesh;
	VAOIndex = Framework::FDraw::BindVAO(CurrentMesh);
}

void Engine::MeshRenderer::AssignTexture(std::string Path) {
	TextureIndex = Framework::FDraw::BindTexture(Path);
}
