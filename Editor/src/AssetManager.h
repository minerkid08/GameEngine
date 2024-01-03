#pragma once
#include <unordered_map>
#include <functional>
#include <filesystem>
#include <Core/UUID.h>
#include "Assets/TextureAsset.h"
namespace Engine{
	class AssetManager{
		public:
		AssetManager();
		~AssetManager();
		void loadAssetsFolder(std::filesystem::path path);
		void load(std::filesystem::path path);
		void addTex(const shdPtr<TextureAsset>& tex, UUID id);
		const shdPtr<TextureAsset>& getTex(UUID id);
		void forEach(std::function<void(const shdPtr<TextureAsset>&, UUID)> func);
		void save();
		private:
		std::unordered_map<UUID, shdPtr<TextureAsset>> textures;
	};
}