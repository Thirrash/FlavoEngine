#pragma once

#include "InternalComponent.h"
#include "EntityX.h"
#include "Mesh.h"
#include <string>

namespace Engine
{
	class MeshRenderer : public InternalComponent<MeshRenderer>
	{
		/*** Constants ***/
		/*** Ctors ***/
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		/*** Fields ***/
	public:
		Mesh CurrentMesh;
		unsigned int ShaderProgram;
		unsigned int VAOIndex;
		unsigned int TextureIndex;

		/*** Methods ***/
	public:
		void AssignMesh(Mesh NewMesh);
		void AssignTexture(std::string Path);
	};
}


