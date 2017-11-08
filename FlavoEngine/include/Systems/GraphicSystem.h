#pragma once

#include "EntityX.h"

class GLFWwindow;

namespace Engine
{
	class Transform;
	class Color;

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

	private:
		void SetTransform(const Transform& Trans, int ShaderProgram);
		void RenderMesh(unsigned int VAOIndex, int ShaderProgram, unsigned int TextureIndex, unsigned int NoIndices);
		static void DrawBackground(Color BckColor);
		static void FinalizeRender();
	};
}