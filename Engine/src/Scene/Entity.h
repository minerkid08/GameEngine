#pragma once
#include "Scene.h"
#include "Components.h"
#include "Core/Log.h"
#include "Core/UUID.h"
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
		operator bool() const {return ent != entt::null;}
		operator int() const {return (int)ent;}
		operator entt::entity() const {return ent;}
		bool operator==(const Entity& other) const {return ent == other.ent && scene == other.scene;}
		bool operator!=(const Entity& other) const {return !(ent == other.ent && scene == other.scene);}
		template<typename T, typename...Args> T& addComp(Args&&... args){
			if(hasComp<T>()){
				Log::Error("Ent already has comp");
			}
			T& comp = scene->registry.emplace<T>(ent, std::forward<Args>(args)...);
			scene->addComp(*this);
			return comp;
		}
		template<typename T> bool hasComp() const {
			return scene->registry.all_of<T>(ent);
		}
		template<typename T> void removeComp(){
			if(!hasComp<T>()){
				Log::Error("Ent doesnt have comp");
			}
			scene->registry.remove<T>(ent);
		}
		template<typename T> T& getComp() const {
			if(!hasComp<T>()){
				Log::Error("Ent doesnt have comp");
			}
			return scene->registry.get<T>(ent);
		}
		UUID getUUID(){
			return getComp<Components::Tag>().uuid;
		}
		private:
		entt::entity ent{entt::null};
		Scene* scene;
	};
}