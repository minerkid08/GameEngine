#include "FileExplorer.h"
namespace Engine{
	FileExplorer::FileExplorer(){
		
	}
	void FileExplorer::reset(){
		memset(filename, 0, sizeof(filename));
	}
	void FileExplorer::setMainPath(const std::string& path){
		mainPath = path;
		curPath = path;
	}
	int FileExplorer::render(const char* ext, bool makeFile){
		ImGui::Begin("File Explorer");
		ImGui::Text(curPath.string().c_str());
		if(ImGui::Button("x")){
			ImGui::End();
			return 2;
		}
		if(curPath != mainPath){
			if(ImGui::Button("<-")){
				curPath = curPath.parent_path();
			}
		}
		if(makeFile){
			ImGui::SameLine();
			ImGui::InputText("path", filename, sizeof(filename));
			ImGui::SameLine();
			if(ImGui::Button("+")){
				outPath = curPath / (std::string(filename) + std::string(ext));
				ImGui::End();
				return 1;
			}
		}
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
					if(p.path().extension() == ext){
						outPath = p.path();
						ImGui::PopID();
						ImGui::End();
						return 1;
					} 
				}
			}
			ImGui::TextWrapped(path.c_str());
			ImGui::NextColumn();
			ImGui::PopID();
		}
		ImGui::End();
		return 0;
	}
}