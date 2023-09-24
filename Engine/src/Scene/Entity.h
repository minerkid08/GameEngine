#pragma once
#include "Scene.h"
#include "Core/Log.h"
#include <entt/ENTT.hpp>
namespace Engine{
	class Entity{
		public:
		Entity(){}
		Entity(Scene* _scene, entt::entity _ent){
			scene = _scene;
			ent = _ent;
		}
		Entity(const Entity& ent2){
			scene = ent2.scene;
			ent = ent2.ent;
		}
		~Entity(){

		}
		operator bool() const {return (int)ent != 0;}
		template<typename T, typename...Args> T& addComp(Args&&... args){
			if(hasComp<T>()){
				Log::Error("Ent already has comp");
			}
			return scene->registry.emplace<T>(ent, std::forward<Args>(args)...);
		}
		template<typename T> bool hasComp(){
			return scene->registry.all_of<T>(ent);
		}
		template<typename T> void removeComp(){
			if(!hasComp<T>()){
				Log::Error("Ent doesnt have comp");
			}
			return scene->registry.remove<T>(ent);
		}
		template<typename T> T& getComp(){
			if(!hasComp<T>()){
				Log::Error("Ent doesnt have comp");
			}
			return scene->registry.get<T>(ent);
		}
		private:
		entt::entity ent;
		Scene* scene;
	};
}