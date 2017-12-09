#include "MeshRenderer.h"
#include "Framework/FDraw.h"
#include "Framework/FUtils.h"


Engine::MeshRenderer::MeshRenderer() {
	VAOIndex = 0;
}

Engine::MeshRenderer::~MeshRenderer() {

}

void Engine::MeshRenderer::AssignMesh(Mesh NewMesh) {
	CurrentMesh = NewMesh;
	VAOIndex = Framework::FDraw::BindVAO(CurrentMesh);
}
