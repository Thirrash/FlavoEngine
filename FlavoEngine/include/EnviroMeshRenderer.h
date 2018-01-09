#pragma once

#include "InternalComponent.h"
#include "EntityX.h"
#include "Mesh.h"
#include "EnviroMaterial.h"
#include <string>

namespace Engine
{
	class EnviroMeshRenderer : public InternalComponent<EnviroMeshRenderer>
	{
		/*** Constants ***/
		/*** Ctors ***/
	public:
		EnviroMeshRenderer();
		virtual ~EnviroMeshRenderer();

		/*** Fields ***/
	public:
		Mesh CurrentMesh;
		EnviroMaterial CurrentMat;
		unsigned int VAOIndex;


		/*** Methods ***/
	public:
		void AssignMesh(Mesh NewMesh);
	};
}
