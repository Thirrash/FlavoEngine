#pragma once

#include "Collider.h"

namespace Engine
{
	class Transform;

	class SphereCollider : public Collider
	{
		friend class CollisionSystem;

		/*** Constants ***/
		/*** Ctors ***/
	public:
		SphereCollider();
		virtual ~SphereCollider();

		/*** Fields ***/
	private:
		float Radius;

		/*** Methods ***/
	public:
		void SetRadius(float Radius);

	protected:
		bool CheckLineCollision(const glm::vec3& LineOrigin, const glm::vec3& LineEnd, Transform* Trans, glm::vec3& CollisionPoint) override;
	};
}
