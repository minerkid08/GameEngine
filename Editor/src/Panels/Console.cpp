#include "Console.h"
#include <iostream>
#include <Engine.h>
namespace Engine{
	Console* Console::instance = nullptr;
	Console::Console(){
		instance = this;
	}
	Console::~Console(){
		instance = nullptr;
	}
	void Console::add(const char* item, int color){
		std::string text = "";
		text += item;
		instance->colors.push_back(color);
		instance->items.push_back(text);
	}
	void Console::clear(){
		colors.clear();
		items.clear();
	}
	void Console::draw(){
		ImGui::Begin("Console");
		if(ImGui::Button("clear")){
			clear();
		}
		for (int i = 0; i < items.size(); i++){
				std::string& item = items[i];
				ImVec4 color;
				switch(colors[i]){
					case 3:
						color = {1.0f, 0.4f, 0.4f, 1.0f};
						ImGui::PushStyleColor(ImGuiCol_Text, color);
						break;
					case 2:
						color = {1.0f, 0.7f, 0.2f, 1.0f};
						ImGui::PushStyleColor(ImGuiCol_Text, color);
						break;
					case 1:
						break;
				}
				ImGui::TextUnformatted(item.c_str());
				if(colors[i] > 1){
					ImGui::PopStyleColor();
				}
			}
		ImGui::End();
	}
}