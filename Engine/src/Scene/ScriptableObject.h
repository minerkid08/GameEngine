#pragma once
#include "Entity.h"
namespace Engine{
	class ScriptableObject{
		public:
		operator bool() const {return (int)ent != 0;}
		template<typename T, typename...Args> T& addComp(Args&&... args){
			if(hasComp<T>()){
				Log::Error("Ent already has comp");
			}
			return ent.addComp<T>(std::forward<Args>(args)...);
		}
		template<typename T> bool hasComp(){
			return ent.hasComp<T>();
		}
		template<typename T> void removeComp(){
			if(!hasComp<T>()){
				Log::Error("Ent doesnt have comp");
			}
			return ent.removeComp<T>();
		}
		template<typename T> T& getComp(){
			if(!hasComp<T>()){
				Log::Error("Ent doesnt have comp");
			}
			return ent.getComp<T>();
		}
		protected:
		virtual void create(){}
		virtual void destroy(){}
		virtual void update(float deltaTime){}
		private:
		friend class Scene;
		Entity ent;
	};
}