#include "Scene.h"
#include "SceneObject.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Debug.h"
#include <OpenGL/assimp/Importer.hpp>
#include <OpenGL/assimp/postprocess.h>
#include <queue>

Engine::Scene::Scene() {
	SceneObject* cameraObj = new SceneObject(entities.create());
	MainCamera = SceneObjectHandle(&entities, cameraObj);
	Objects.insert(std::pair<Entity::Id, SceneObjectHandle>(cameraObj->Id.id(), MainCamera));
}

Engine::Scene::~Scene() {

}

Engine::SceneObjectHandle Engine::Scene::Instantiate() {
	SceneObject* newObj = new SceneObject(entities.create());
	SceneObjectHandle handle(&entities, newObj);
	Objects.insert(std::pair<Entity::Id, SceneObjectHandle>(newObj->Id.id(), handle));

	return handle;
}

Engine::SceneObjectHandle Engine::Scene::Instantiate(std::string ModelPath) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(ModelPath, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		LogR("ERROR ASSIMP -> ", importer.GetErrorString());
		return SceneObjectHandle();
	}

	string directory = ModelPath.substr(0, ModelPath.find_last_of('/'));
	SceneObjectHandle handle;
	ProcessModelNode(scene->mRootNode, scene, handle, SceneObjectHandle(), directory);
	return handle;
}

bool Engine::Scene::Destroy(Engine::SceneObjectHandle Object) {
	if (!Object.IsValid()) {
		return false;
	}

	auto it = Objects.find(Object.Get()->Id.id());
	if (it == Objects.end()) {
		return false;
	}

	Object.Destroy();
	Objects.erase(it);
}

Engine::EventManager& Engine::Scene::GetEventManager() {
	return events;
}

void Engine::Scene::ChangeParent(ComponentHandle<Transform> Parent, ComponentHandle<Transform> Child) {
	if (!Parent.IsValid() || !Child.IsValid())
		return;

	Transform* parent = Parent.Get();
	Transform* child = Child.Get();

	if (child->Parent.IsValid()) {
		child->Parent.Get()->Children.erase(child->AssignedTo->Id);
	}

	child->Parent = Parent;
	child->bHasParentChanged = true;
	parent->Children.insert(std::pair<Entity, ComponentHandle<Transform>>(child->AssignedTo->Id, Child));
}

void Engine::Scene::ProcessModelNode(aiNode* Node, const aiScene* AiScene, SceneObjectHandle& RootObject, SceneObjectHandle& Parent, std::string Directory) {
	SceneObjectHandle handle;
	if (Node->mNumMeshes > 0) {
		aiMesh* mesh = AiScene->mMeshes[Node->mMeshes[0]];

		handle = Instantiate();
		ComponentHandle<MeshRenderer> renderer = handle.Get()->Add<MeshRenderer>();
		float* vertices = new float[mesh->mNumVertices * 5];
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			vertices[i * 5] = mesh->mVertices[i].x;
			vertices[i * 5 + 1] = mesh->mVertices[i].y;
			vertices[i * 5 + 2] = mesh->mVertices[i].z;

			if (mesh->mTextureCoords[0] != nullptr) {
				vertices[i * 5 + 3] = mesh->mTextureCoords[0][i].x;
				vertices[i * 5 + 4] = mesh->mTextureCoords[0][i].y;
			} else {
				vertices[i * 5 + 3] = 0.0f;
				vertices[i * 5 + 4] = 0.0f;
				LogW("Null texture coords");
			}
		}

		unsigned int* indices = new unsigned int[mesh->mNumFaces * 3];
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			indices[i * 3] = mesh->mFaces[i].mIndices[0];
			indices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
			indices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
		}

		renderer->AssignMesh(Mesh(vertices, mesh->mNumVertices * 5, indices, mesh->mNumFaces * 3));
		if (mesh->mMaterialIndex >= 0) {
			aiMaterial* material = AiScene->mMaterials[mesh->mMaterialIndex];
			if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
				aiString textPath;
				material->GetTexture(aiTextureType_DIFFUSE, 0, &textPath);
				std::string truePath = textPath.C_Str();
				renderer->AssignTexture(truePath);
			}
		}

		if (Parent.IsValid()) {
			ChangeParent(Parent.Get()->Get<Transform>(), handle.Get()->Get<Transform>());
			LogA("Parented");
		}

		if (!RootObject.IsValid())
			RootObject = handle;
	}

	LogB("Loaded mesh. NoChildrens: ", Node->mNumChildren);
	for (unsigned int i = 0; i < Node->mNumChildren; i++) {
		ProcessModelNode(Node->mChildren[i], AiScene, RootObject, handle, Directory);
	}
}
