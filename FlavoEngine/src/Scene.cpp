#include "Scene.h"
#include "SceneObject.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Debug.h"
#include <OpenGL/assimp/Importer.hpp>
#include <OpenGL/assimp/postprocess.h>
#include <queue>
#include "BoxCollider.h"

Engine::Scene::Scene() {
	SceneObject* cameraObj = new SceneObject(entities.create());
	ComponentHandle<Camera> cam = cameraObj->Add<Camera>();
	cam.Get()->configure(events);

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
		handle.Get()->Name = Node->mName.C_Str();
		ComponentHandle<Transform> transform = handle.Get()->Get<Transform>();

		aiVector3D pos, scale;
		aiQuaterniont<float> rot;
		Node->mTransformation.Decompose(scale, rot, pos);

		glm::vec3 scalev(1.0f, 1.0f, 1.0f);
		if (Parent.IsValid())
			scalev = glm::vec3(scale.x, scale.y, scale.z) * Parent.Get()->Get<Transform>().Get()->Scale;

		transform.Get()->SetLocalPosition(glm::vec3(pos.x, pos.y, pos.z));
		transform.Get()->SetLocalRotation(glm::quat(rot.x, rot.y, rot.z, rot.w));
		transform.Get()->SetLocalScale(glm::vec3(scale.x, scale.y, scale.z));
		LogB(Node->mName.C_Str(), pos.x, pos.y, pos.z, scale.x, scale.y, scale.z);

		ComponentHandle<MeshRenderer> renderer = handle.Get()->Add<MeshRenderer>();
		ComponentHandle<BoxCollider> collider = handle.Get()->Add<BoxCollider>();

		float maxDistance[3]{ -9999999.9f, -9999999.9f , -9999999.9f };
		float minDistance[3]{ 9999999.9f, 9999999.9f , 9999999.9f };
		float* vertices = new float[mesh->mNumVertices * 8];
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			if (mesh->mVertices[i].x > maxDistance[0])
				maxDistance[0] = mesh->mVertices[i].x;
			if (mesh->mVertices[i].y > maxDistance[1])
				maxDistance[1] = mesh->mVertices[i].y;
			if (mesh->mVertices[i].z > maxDistance[2])
				maxDistance[2] = mesh->mVertices[i].z;

			if (mesh->mVertices[i].x < minDistance[0])
				minDistance[0] = mesh->mVertices[i].x;
			if (mesh->mVertices[i].y < minDistance[1])
				minDistance[1] = mesh->mVertices[i].y;
			if (mesh->mVertices[i].z < minDistance[2])
				minDistance[2] = mesh->mVertices[i].z;

			vertices[i * 8] = mesh->mVertices[i].x;
			vertices[i * 8 + 1] = mesh->mVertices[i].y;
			vertices[i * 8 + 2] = mesh->mVertices[i].z;

			vertices[i * 8 + 3] = mesh->mNormals->x;
			vertices[i * 8 + 4] = mesh->mNormals->y;
			vertices[i * 8 + 5] = mesh->mNormals->z;

			if (mesh->mTextureCoords[0] != nullptr) {
				vertices[i * 8 + 6] = mesh->mTextureCoords[0][i].x;
				vertices[i * 8 + 7] = mesh->mTextureCoords[0][i].y;
			} else {
				vertices[i * 8 + 6] = 0.0f;
				vertices[i * 8 + 7] = 0.0f;
				LogW("Null texture coords");
			}
		}

		//LogD(minDistance[0] * scale.x * scalev.x, maxDistance[0] * scale.x * scalev.x, minDistance[1] * scale.x * scalev.x, maxDistance[1] * scale.x * scalev.x, minDistance[2] * scale.x * scalev.x, maxDistance[2] * scale.x * scalev.x);
		collider.Get()->SetBox(minDistance[0] * scale.x * scalev.x, maxDistance[0] * scale.x * scalev.x, minDistance[1] * scale.x * scalev.x, maxDistance[1] * scale.x * scalev.x, minDistance[2] * scale.x * scalev.x, maxDistance[2] * scale.x * scalev.x);
		unsigned int* indices = new unsigned int[mesh->mNumFaces * 3];
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			indices[i * 3] = mesh->mFaces[i].mIndices[0];
			indices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
			indices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
		}

		renderer->AssignMesh(Mesh(vertices, mesh->mNumVertices * 8, indices, mesh->mNumFaces * 3));
		if (mesh->mMaterialIndex >= 0) {
			aiMaterial* material = AiScene->mMaterials[mesh->mMaterialIndex];
			if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
				aiString textPath;
				material->GetTexture(aiTextureType_DIFFUSE, 0, &textPath);
				std::string truePath = textPath.C_Str();
				renderer->CurrentMat.AssignTexture(Directory + "/" + truePath);
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
