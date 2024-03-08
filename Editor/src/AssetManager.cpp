#include "AssetManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace Engine{
	AssetManager* AssetManager::instance = nullptr;
	AssetManager::AssetManager(){
		textures = {};
		instance = this;
	}
	AssetManager::~AssetManager(){
		for(auto& [id, tex] : textures){
			textures[id] = nullptr;
		}
	}
	void AssetManager::loadAssetsFolder(std::filesystem::path path){
		std::vector<std::filesystem::path> folders;
		assetFolderPath = path;
		folders.push_back(path);

		while(folders.size() > 0){
			std::filesystem::path curFolder = folders[0];
			for(int j = 1; j < folders.size(); j++){
				folders[j - 1] = folders[j];
			}
			folders.resize(folders.size() - 1);

			for(auto file : std::filesystem::directory_iterator(curFolder)){
				if(file.is_directory()){
					if(file.path().filename() == ".vscode" || file.path().filename() == ".git"){
						continue;
					}
					folders.push_back(file.path());
				}else{
					if(file.path().extension() == ".tex"){
						shdPtr<TextureAsset> asset = std::make_shared<TextureAsset>();
						asset->loadFromAsset(file.path());
						addTex(asset, asset->getId());
					}
				}
			}
		}
	}
	void AssetManager::load(std::filesystem::path path){
		std::vector<std::filesystem::path> folders;
		folders.push_back(path);

		while(folders.size() > 0){
			std::filesystem::path curFolder = folders[0];
			for(int j = 1; j < folders.size(); j++){
				folders[j - 1] = folders[j];
			}
			folders.resize(folders.size() - 1);

			for(auto file : std::filesystem::directory_iterator(curFolder)){
				if(file.is_directory()){
					if(file.path().filename() == ".vscode" || file.path().filename() == ".git"){
						continue;
					}
					folders.push_back(file.path());
				}else{
					if(file.path().extension() == ".png"){
						std::string path = file.path().string();
						if(std::filesystem::exists(path.substr(0, path.size() - 4) + ".tex")){
							continue;
						}
						shdPtr<TextureAsset> asset = std::make_shared<TextureAsset>();
						asset->create(path.substr(0, path.size() - 4) + ".tex");
						asset->save();
						addTex(asset, asset->getId());
					}
				}
			}
		}
	}
	void AssetManager::updateAssets(){
		std::vector<std::filesystem::path> folders;
		folders.push_back(assetFolderPath);

		while(folders.size() > 0){
			std::filesystem::path curFolder = folders[0];
			for(int j = 1; j < folders.size(); j++){
				folders[j - 1] = folders[j];
			}
			folders.resize(folders.size() - 1);

			for(auto file : std::filesystem::directory_iterator(curFolder)){
				if(file.is_directory()){
					if(file.path().filename() == ".vscode" || file.path().filename() == ".git"){
						continue;
					}
					folders.push_back(file.path());
				}else{
					if(file.path().extension() == ".png"){
						std::string path = file.path().string();
						if(std::filesystem::exists(path.substr(0, path.size() - 4) + ".tex")){
							getTex(path.substr(0, path.size() - 4) + ".tex")->reload();
							continue;
						}
						shdPtr<TextureAsset> asset = std::make_shared<TextureAsset>();
						asset->create(path.substr(0, path.size() - 4) + ".tex");
						asset->save();
						addTex(asset, asset->getId());
					}
				}
			}
		}
	}
	void AssetManager::addTex(const shdPtr<TextureAsset>& tex, UUID id){
		textures.emplace(id, tex);
	}

	const shdPtr<TextureAsset>& AssetManager::getTex(UUID id){
		return textures.at(id);
	}

	const shdPtr<TextureAsset>& AssetManager::getTex(std::filesystem::path path){
		std::stringstream ss;
		std::ifstream stream(path);
		ss << stream.rdbuf();
		nlohmann::json j = nlohmann::json::parse(ss);
		UUID id = (uint64_t)j["id"];
		if(textures.find(id) == textures.end()){
			std::cout << "tex " << id << " not in list" << std::endl;
		}
		return textures[id];
	}

	void AssetManager::save(){
		for(auto [id, tex] : textures){
			tex->save();
		}
	}
	void AssetManager::forEach(std::function<void(const shdPtr<TextureAsset>&, UUID)> func){
		for(auto [id, tex] : textures){
			func(tex, id);
		}
	}
}