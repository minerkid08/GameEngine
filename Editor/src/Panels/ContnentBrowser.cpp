#include "ContnentBrowser.h"
namespace Engine{
	ContentBrowser::ContentBrowser(){

	}
	void ContentBrowser::setMainPath(const std::string& path){
		mainPath = path;
		curPath = path;
	}
	void ContentBrowser::render(const shdPtr<AssetManager>& assetManager){
		ImGui::Begin("Content Browser");
		if(ImGui::Button("r")){
			AssetManager::instance->updateAssets();
		}
		ImGui::SameLine();
		ImGui::Text(curPath.string().c_str());
		if(curPath != mainPath){
			ImGui::SameLine();
			if(ImGui::Button("<-")){
				curPath = curPath.parent_path();
			}
		}
		buttonSize = ImGui::GetIO().FontGlobalScale * 150;
		float cellSize = buttonSize + padding;
		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columCount = (int)(panelWidth / cellSize);
		if(columCount < 1){
			columCount = 1;
		}
		ImGui::BeginTable("table", columCount, ImGuiTableFlags_SizingFixedFit);
		ImGui::TableNextColumn();
		int i = 0;
		for(auto& p : std::filesystem::directory_iterator(curPath)){
			std::filesystem::path path2 = p.path().filename();
			std::string extension = path2.extension().string().substr(__min(1, path2.extension().string().size()));
			if(extension == "png"){
				continue;
			}
			std::string path = path2.string().substr(0, path2.string().size() - extension.size());
			ImGui::PushID(i++);
			if(p.is_directory()){
				auto name = p.path().filename().string();
				if(ImGui::Button("folder", ImVec2(buttonSize, buttonSize))){
					curPath /= name;
				}
			}else{
				if(ImGui::Button(extension.c_str(), ImVec2(buttonSize, buttonSize))){
					ImGui::OpenPopup("CBCtxMenu");
					ctxMenuPath = p.path();
				}
				if(ImGui::BeginDragDropSource()){
					const wchar_t* data = p.path().c_str();
					ImGui::SetDragDropPayload("ContentBrowserItem", data, (wcslen(data) + 1) * sizeof(wchar_t), ImGuiCond_Once);
					ImGui::EndDragDropSource();
				}
			}
			ImGui::TextWrapped(path.c_str());
			ImGui::TableNextColumn();
			ImGui::PopID();
		}
		ImGui::EndTable();
		ImGui::End();
		if(ImGui::BeginPopup("CBCtxMenu")){
			if(ImGui::MenuItem("makeAsset")){
				shdPtr<TextureAsset> asset = std::make_shared<TextureAsset>();
				asset->create(ctxMenuPath);
				asset->save();
				assetManager->addTex(asset, asset->getId());
			}
			ImGui::EndPopup();
		}
	}
}