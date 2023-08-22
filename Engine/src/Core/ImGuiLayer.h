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

		void begin();
		void end();
		private:
		float time = 0;
	};
}