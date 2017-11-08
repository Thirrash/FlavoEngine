#include "Mesh.h"

Engine::Mesh::Mesh() {

}

Engine::Mesh::Mesh(float * VertexArray, unsigned int VertexCount, unsigned int * IndicesArray, unsigned int IndexCount) : Vertices(VertexArray), NoVertices(VertexCount), Indices(IndicesArray), NoIndices(IndexCount) {

}

Engine::Mesh::~Mesh() {
	//delete Vertices;
	//delete Indices;
}
