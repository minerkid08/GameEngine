#include "TextureAsset.h"
#include <fstream>
#include <Core/Log.h>
namespace Engine{
	TextureAsset::TextureAsset(){

	}

	TextureAsset::~TextureAsset(){

	}

	void TextureAsset::loadFromAsset(std::filesystem::path newPath){
		std::filesystem::path texPath = newPath;
		texPath.replace_extension(".png");
		std::string pathString = texPath.string();
		tex = std::make_shared<Texture2D>(pathString);
		Log::Info((std::string("loading: ") + texPath.string()).c_str());
		std::ifstream stream(newPath);
		std::stringstream sstream;
		sstream << stream.rdbuf();
		nlohmann::json j = nlohmann::json::parse(sstream);
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

	void TextureAsset::reload(){
		std::filesystem::path path2 = path.string();
		path2.replace_extension(".png");
		tex->loadFromFile(path2.string());
	}

	void TextureAsset::save(){
		nlohmann::json j;
		j["id"] = (uint64_t)id;
		std::ofstream ofstream(path);
		ofstream << j.dump(4);
	}

	const shdPtr<Texture2D>& TextureAsset::getTexture(){
		return tex;
	}
}