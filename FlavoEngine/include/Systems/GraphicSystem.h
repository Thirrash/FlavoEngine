#pragma once

#include "EntityX.h"
#include "Skybox.h"
#include "Postprocess.h"
#include "Input.h"
#include "OpenGL/glm/glm.hpp"

class GLFWwindow;

namespace Engine
{
	class Transform;
	class Color;
	class DirectionalLight;
	class PointLight;
	class SpotLight;

	class GraphicSystem : public System<GraphicSystem>, public Receiver<MouseInput>
	{
		/*** Constants ***/
		/*** Ctors ***/
	public:
		GraphicSystem();
		~GraphicSystem();

		/*** Fields ***/
		/*** Methods ***/
	public:
		void configure(EventManager& event_manager);
		void receive(const MouseInput& Input);

		void Update(EntityManager& es, EventManager& events, TimeDelta dt) override;
		void DrawBackground(Color BckColor);
		void FinalizeRender();

	private:
		void SetTransform(Transform* Trans, int ShaderProgram);
		void RenderMesh(unsigned int VAOIndex, int ShaderProgram, unsigned int TextureIndex, unsigned int NoIndices);

		void SetDirectionalLight(int ShdaerProgram, DirectionalLight* Light);
		void SetPointLight(int ShaderProgram, PointLight* Light, int Index);
		void SetSpotLight(int ShaderProgram, SpotLight* Light);

		void DrawSkybox();

	private:
		Skybox skybox_;
		Postprocess postprocess_;
		glm::vec2 mousePos_;
		float lensToggle_;
		bool xPressed_;

		unsigned int raymarchShader_;
	};
}