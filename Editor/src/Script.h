#pragma once
#include <iostream>
#include <Engine.h>
namespace Engine{
	class Script : public ScriptableObject{
		public:
		void create(){
		}
		void destroy(){
		}
		void update(float deltaTime){
			auto& transformComp = getComp<Components::Transform>();
			if(Input::keyDown(EngineKeycode_W)){
				transformComp.pos.y -= deltaTime;
			}
			if(Input::keyDown(EngineKeycode_S)){
				transformComp.pos.y += deltaTime;
			}
			if(Input::keyDown(EngineKeycode_A)){
				transformComp.pos.x -= deltaTime;
			}
			if(Input::keyDown(EngineKeycode_D)){
				transformComp.pos.x += deltaTime;
			}
		}
	};
}