#pragma once
#include <Engine.h>
#include <filesystem>
namespace Engine{
	class FileExplorer{
		public:
		FileExplorer();
		void setMainPath(const std::string& path);
		int render(const char* ext, bool makeFile);
		void reset();
		int buttonSize = 256;
		float padding = 16.0f;
		std::filesystem::path outPath;
		private:
		std::filesystem::path mainPath;
		std::filesystem::path curPath;
		char filename[256];
	};
}