#pragma once

#include "EntityX.h"
#include <OpenGL/glm/glm.hpp>
#include <map>
#include <vector>
#include <functional>

namespace Engine
{
	class Collider;
	class Transform;

	class CollisionSystem : public System<CollisionSystem>
	{
	private:
		class Vec3Hasher
		{
		public:
			size_t operator ()(const glm::vec3& Key) const {
				float inv = 1.0f / CellSize;
				size_t xHash = std::hash<float>()(Key.x * inv);
				size_t yHash = std::hash<float>()(Key.y * inv);
				size_t zHash = std::hash<float>()(Key.z * inv);
				return (xHash ^ (yHash << 1)) ^ zHash;
				//return ((int)std::floor(Key.x * inv) * 73856093) ^ ((int)std::floor(Key.y * inv) * 19349663) ^ ((int)std::floor(Key.z * inv) * 83492791);
			}
		};

		/*** Constants ***/
		/*** Ctors ***/
	public:
		CollisionSystem();
		~CollisionSystem();

		/*** Fields ***/
	private:
		static float CellSize;
		static std::unordered_map<glm::vec3, std::set<ComponentHandle<Collider>>, Vec3Hasher> CollidingMap;

		/*** Methods ***/
	public:
		static bool Raycast(const glm::vec3& Origin, const glm::vec3& End, ComponentHandle<Collider>& HitCollider, glm::vec3& HitPoint);
		void Update(EntityManager& es, EventManager& events, TimeDelta dt) override;

	private:
		void UpdateCollidingMap(ComponentHandle<Collider>& ColliderHandle, ComponentHandle<Transform>& TransformHandle);
	};
}