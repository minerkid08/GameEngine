#pragma once

#include <filesystem>
#include <renderer/Texture.h>
#include <Core/UUID.h>
#include <json/json.hpp>

namespace Engine{
	class TextureAsset{
		public:
		TextureAsset();
		~TextureAsset();
		void loadFromAsset(std::filesystem::path newPath);
		void create(std::filesystem::path newPath);
		void save();
		void reload();
		const shdPtr<Texture2D>& getTexture();
		UUID getId(){return id;}
		private:
		std::filesystem::path path;
		UUID id;
		shdPtr<Texture2D> tex;
	};
}