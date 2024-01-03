#include "AssetManager.h"

namespace Engine{
	AssetManager::AssetManager(){

	}
	AssetManager::~AssetManager(){

	}
	void AssetManager::loadAssetsFolder(std::filesystem::path path){
		for(auto folder : std::filesystem::directory_iterator(path)){
			if(folder.is_directory()){

			}else{
				if(folder.path().extension() == ".tex"){
					shdPtr<TextureAsset> asset = std::make_shared<TextureAsset>();
					asset->loadFromAsset(folder.path());
					addTex(asset, asset->getId());
				}
			}
		}
	}
	void AssetManager::load(std::filesystem::path path){
		
	}
	void AssetManager::addTex(const shdPtr<TextureAsset>& tex, UUID id){
		textures.insert({id, tex});
	}

	const shdPtr<TextureAsset>& AssetManager::getTex(UUID id){
		return textures.at(id);
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