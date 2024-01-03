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
		ImGui::Text(curPath.string().c_str());
		if(curPath != mainPath){
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
		ImGui::Columns(columCount, 0, false);
		int i = 0;
		for(auto& p : std::filesystem::directory_iterator(curPath)){
			ImGui::PushID(i++);
			std::string path = p.path().filename().string();
			if(p.is_directory()){
				auto name = p.path().filename();
				if(ImGui::Button("folder.png", ImVec2(buttonSize, buttonSize))){
					curPath /= name;
				}
			}else{
				if(ImGui::Button("file.png", ImVec2(buttonSize, buttonSize))){
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
			ImGui::NextColumn();
			ImGui::PopID();
		}
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