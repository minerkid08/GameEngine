#pragma once
#include "Layer.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include <imgui/imgui.h>

namespace Engine{
	class ImGuiLayer : public Layer{
		public:
		ImGuiLayer() : Layer("ImGui"){}
		~ImGuiLayer(){}

		void attach();
		void detach();
		void update(float deltaTime);
		void imGuiRender();
		void event(Event* e);

		void setBlockEvents(bool e){blockEvents = e;}

		void begin();
		void end();
		private:
		bool blockEvents = true;
		float time = 0;
	};
}