#pragma once

#include "Collider.h"

namespace Engine
{
	class Transform;

	class BoxCollider : public Collider
	{
		friend class CollisionSystem;

		/*** Constants ***/
		/*** Ctors ***/
	public:
		BoxCollider();
		virtual ~BoxCollider();

		/*** Fields ***/
		/*** Methods ***/
	public:
		void SetBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);

	protected:
		bool CheckLineCollision(const glm::vec3& LineOrigin, const glm::vec3& LineEnd, Transform* Trans, glm::vec3& CollisionPoint) override;
	};
}
