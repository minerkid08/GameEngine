#include "TextureAsset.h"

namespace Engine{
	TextureAsset::TextureAsset(){

	}

	TextureAsset::~TextureAsset(){

	}

	void TextureAsset::loadFromAsset(std::filesystem::path newPath){
		std::filesystem::path texPath = newPath;
		texPath.replace_extension(".png");
		std::string pathString = newPath.string();
		tex = std::make_shared<Texture2D>(pathString);
		nlohmann::json j(newPath);
		id = (uint64_t)j["id"];
		path = newPath;	
	}

	void TextureAsset::create(std::filesystem::path newPath){
		std::string pathString = newPath.string();
		tex = std::make_shared<Texture2D>(pathString);
		newPath.replace_extension(".tex");
		id = UUID();
		path = newPath;
	}

	void TextureAsset::save(){
		nlohmann::json j(path);
		j["id"] = (uint64_t)id;
	}

	const shdPtr<Texture2D>& TextureAsset::getTexture(){
		return tex;
	}
}