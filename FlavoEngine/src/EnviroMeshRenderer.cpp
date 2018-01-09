#include "EnviroMeshRenderer.h"
#include "Framework/FDraw.h"
#include "Framework/FUtils.h"


Engine::EnviroMeshRenderer::EnviroMeshRenderer() {
	VAOIndex = 0;
}

Engine::EnviroMeshRenderer::~EnviroMeshRenderer() {

}

void Engine::EnviroMeshRenderer::AssignMesh(Mesh NewMesh) {
	CurrentMesh = NewMesh;
	VAOIndex = Framework::FDraw::BindVAO(CurrentMesh);
}
