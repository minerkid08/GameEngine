#pragma once
#include <Engine.h>
#include <filesystem>
namespace Engine{
	class ContentBrowser{
		public:
		ContentBrowser();
		void setMainPath(const std::string& path);
		void render();
		int buttonSize = 256;
		float padding = 16.0f;
		private:
		std::filesystem::path mainPath;
		std::filesystem::path curPath;
	};
}