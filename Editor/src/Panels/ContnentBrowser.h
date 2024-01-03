#pragma once
#include <Engine.h>
#include <filesystem>
#include "AssetManager.h"
namespace Engine{
	class ContentBrowser{
		public:
		ContentBrowser();
		void setMainPath(const std::string& path);
		void render(const shdPtr<AssetManager>& assetManager);
		int buttonSize = 256;
		float padding = 16.0f;
		private:
		std::filesystem::path mainPath;
		std::filesystem::path curPath;
		std::filesystem::path ctxMenuPath;
	};
}