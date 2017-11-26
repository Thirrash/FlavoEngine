#pragma once

#include "InternalComponent.h"
#include "EntityX.h"
#include <OpenGL/glm/glm.hpp>
#include <vector>

namespace Engine
{
	class GlmVec3Comparer
	{
	public:
		bool operator ()(const glm::vec3& first, const glm::vec3& second) const;
	};

	class Transform;

	class Collider : public InternalComponent<Collider>
	{
		friend class CollisionSystem;

		/*** Constants ***/
		/*** Ctors ***/
	public:
		Collider();
		virtual ~Collider();

		/*** Fields ***/
	protected:
		std::vector<glm::vec2> WorldBoundingBox;
		std::vector<glm::vec2> LocalBoundingBox;
		std::set<glm::vec3, GlmVec3Comparer> CurrentCells;

		bool bIsDirty;

		/*** Methods ***/
	protected:
		virtual bool CheckLineCollision(const glm::vec3& LineOrigin, const glm::vec3& LineEnd, Transform* Trans, glm::vec3& CollisionPoint) = 0;
		void SetLocalBoundingBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);
	};
}
