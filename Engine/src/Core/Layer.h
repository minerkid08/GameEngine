#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Engine{
	class Layer{
		public:
		Layer(const std::string& _name = "naem") : name(_name){}

		virtual void attach(){}
		virtual void detach(){}
		virtual void update(float deltaTime){}
		virtual void event(Event* event){}
		virtual void imGuiRender(){}

		inline const std::string& getName() {return name;}
		private:
		std::string name;
	};
}