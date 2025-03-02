#pragma once
#include <unordered_map>
#include <functional>
#include <filesystem>
#include <Core/UUID.h>
#include "Assets/TextureAsset.h"
namespace Engine{
	class AssetManager{
		public:
		static AssetManager* instance;
		AssetManager();
		~AssetManager();
		void loadAssetsFolder(std::filesystem::path path);
		void load(std::filesystem::path path);
		void updateAssets();
		void addTex(const shdPtr<TextureAsset>& tex, UUID id);
		const shdPtr<TextureAsset>& getTex(UUID id);
		const shdPtr<TextureAsset>& getTex(std::filesystem::path path);
		void forEach(std::function<void(const shdPtr<TextureAsset>&, UUID)> func);
		void save();
		private:
		std::unordered_map<UUID, shdPtr<TextureAsset>> textures;
		std::filesystem::path assetFolderPath;
	};
}