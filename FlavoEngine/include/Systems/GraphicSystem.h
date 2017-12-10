#pragma once

#include "EntityX.h"

class GLFWwindow;

namespace Engine
{
	class Transform;
	class Color;
	class DirectionalLight;
	class PointLight;
	class SpotLight;

	class GraphicSystem : public System<GraphicSystem>
	{
		/*** Constants ***/
		/*** Ctors ***/
	public:
		GraphicSystem();
		~GraphicSystem();

		/*** Fields ***/
		/*** Methods ***/
	public:
		void Update(EntityManager& es, EventManager& events, TimeDelta dt) override;
		void DrawBackground(Color BckColor);
		void FinalizeRender();

	private:
		void SetTransform(Transform* Trans, int ShaderProgram);
		void RenderMesh(unsigned int VAOIndex, int ShaderProgram, unsigned int TextureIndex, unsigned int NoIndices);

		void SetDirectionalLight(int ShdaerProgram, DirectionalLight* Light);
		void SetPointLight(int ShaderProgram, PointLight* Light, int Index);
		void SetSpotLight(int ShaderProgram, SpotLight* Light);
	};
}