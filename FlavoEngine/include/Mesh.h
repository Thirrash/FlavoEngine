#pragma once

namespace Engine
{
	class Mesh
	{
		/*** Constants ***/
		/*** Ctors ***/
	public:
		Mesh();
		Mesh(float* VertexArray, unsigned int VertexCount, unsigned int* IndicesArray, unsigned int IndexCount);
		~Mesh();

		/*** Fields ***/
	public:
		float* Vertices;
		unsigned int NoVertices;

		unsigned int* Indices;
		unsigned int NoIndices;

		/*** Methods ***/
	};
}