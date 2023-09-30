#pragma once
#include <imgui/imgui.h>
#include <string>
#include <vector>
#include <string>
namespace Engine{
	class Console{
		public:
		Console();
		~Console();
		void clear();
		void draw();
		static void add(const char* data, int color);
		private:
		static Console* instance;
		std::vector<std::string> items;
		std::vector<int> colors;
	};
}