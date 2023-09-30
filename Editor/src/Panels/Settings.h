#pragma once
#include <imgui/imgui.h>
namespace Engine{
	class SettingsPanel{
		public:
		static float scaleAllSizes;
		void draw(){
			ImGui::Begin("Settings");
			ImGuiIO& io = ImGui::GetIO();
			ImGui::SliderFloat("UiScale", &scaleAllSizes, 0.5, 2.5);
			io.FontGlobalScale = scaleAllSizes;
			ImGui::End();
			ImGuiStyle& style = ImGui::GetStyle();
			style.WindowMinSize.x = 48 * scaleAllSizes;
			style.WindowMinSize.y = 48 * scaleAllSizes;
		}
	};
}