#pragma once
#include <entt/ENTT.hpp>
#include "Core/Core.h"
namespace Engine{
	class API Entity;
	class API Scene{
		public:
		Scene();
		~Scene();
		void update(float deltaTime);
		void viewportResize(int width, int height, float zoom);

		Entity createEnt(const std::string& name = "thing with no name");
		void removeEnt(const Entity& ent);

		entt::registry& getReg(){return registry;}
		private:
		int width = 0;
		int height = 0;
		friend class Entity;
		entt::registry registry;
	};
}