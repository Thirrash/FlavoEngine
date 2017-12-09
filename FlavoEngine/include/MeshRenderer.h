#pragma once

#include "InternalComponent.h"
#include "EntityX.h"
#include "Mesh.h"
#include "Material.h"
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
		Material CurrentMat;
		unsigned int VAOIndex;


		/*** Methods ***/
	public:
		void AssignMesh(Mesh NewMesh);
	};
}


