#include "FileExplorer.h"
namespace Engine{
	FileExplorer::FileExplorer(){
		
	}
	void FileExplorer::reset(int _flags){
		flags = _flags;
		memset(filename, 0, sizeof(filename));
		if(flags & FileExplorerFlags_AlwaysShowBack){
			curPath = std::filesystem::absolute(mainPath);
			Log::Info(curPath.string());
		}else{
			curPath = mainPath;
		}
	}
	void FileExplorer::setMainPath(const std::string& path){
		mainPath = path;
		curPath = path;
	}
	int FileExplorer::render(const char* ext){
		if (flags & FileExplorerFlags_MakeFile && flags & FileExplorerFlags_DontShowFiles){
			Log::Error("Explorer: invalid flag combination - makeFile + dontShowFiles");
			return 2;
		}
		
		ImGui::Begin("File Explorer", nullptr, ImGuiWindowFlags_NoDocking);
		if(ImGui::Button("x")){
			ImGui::End();
			return 2;
		}
		if(curPath != mainPath || flags & FileExplorerFlags_AlwaysShowBack){
			ImGui::SameLine();
			if(ImGui::Button("<-")){
				curPath = curPath.parent_path();
			}
		}
		if(flags & FileExplorerFlags_DontShowFiles){
				ImGui::SameLine();
			if(ImGui::Button("+")){
				outPath = curPath;
				ImGui::End();
				return 1;
			}
		}
		if(flags & FileExplorerFlags_MakeFile){
			ImGui::SameLine();
			if(ImGui::Button("+")){
				outPath = curPath / (std::string(filename) + std::string(ext));
				ImGui::End();
				return 1;
			}
			ImGui::SameLine();
			ImGui::Text(curPath.string().c_str());
			ImGui::InputText(" ", filename, sizeof(filename));
		}else{
			ImGui::SameLine();
			ImGui::Text(curPath.string().c_str());
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
				if(!(flags & FileExplorerFlags_DontShowFolders)){
					auto name = p.path().filename();
					if(ImGui::Button("folder.png", ImVec2(buttonSize, buttonSize))){
						curPath /= name;
					}
					ImGui::TextWrapped(path.c_str());
					ImGui::NextColumn();
				}
			}else{
				if(!(flags & FileExplorerFlags_DontShowFiles)){
					if(ImGui::Button("file.png", ImVec2(buttonSize, buttonSize))){
						if(p.path().extension() == ext){
							outPath = p.path();
							ImGui::PopID();
							ImGui::End();
							return 1;
						} 
					}
					ImGui::TextWrapped(path.c_str());
					ImGui::NextColumn();
				}
			}
			ImGui::PopID();
		}
		ImGui::End();
		return 0;
	}
}