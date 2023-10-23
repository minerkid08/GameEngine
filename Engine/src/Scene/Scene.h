#pragma once
#include <entt/ENTT.hpp>
#include "Core/Core.h"
#include "Renderer/Camera.h"
namespace Engine{
	class Entity;
	class API Scene{
		public:
		std::vector<Entity> entities;
		Scene();
		~Scene();
		void updateRuntime(float deltaTime);
		void updateEditor(float deltaTime);
		void updateEditor(float deltaTime, Camera& camera);
		void viewportResize(int width, int height);

		Entity createEnt(const std::string& name = "thing with no name");
		void removeEnt(const Entity& ent);
		Entity getEntityByName(const std::string& name);
		void moveEnt(const Entity& ent, int mod);

		void stop();

		void addComp(Entity& ent);

		shdPtr<Scene> copy();

		entt::registry& getReg(){return registry;}
		private:
		int width = 0;
		int height = 0;
		friend class Entity;
		entt::registry registry;
	};
}