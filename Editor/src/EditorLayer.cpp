#include "EditorLayer.h"

namespace Engine{
	EditorLayer::EditorLayer() : Layer("e"), editorCamera(0.0f){}
	void EditorLayer::attach(){
		Log::callback = [](const std::string& s, int c){
			const char* str = s.c_str();
			Console::add(str, c);
		};
		scene = std::make_shared<Scene>();
		contentBrowser.setMainPath("Assets");
		explorer.setMainPath("Assets");

		serializer.setEnt(scene);

		sceneHierarchy.setContext(scene);

		open = new bool(false);
		FrameBufferSpec spec;
		spec.width = 1280;
		spec.height = 720;
		frameBuffer = std::make_shared<FrameBuffer>(spec);
		Console::add("inited", 1);
	}
	EditorLayer::~EditorLayer(){
	}
	void EditorLayer::detach(){

	}
	void EditorLayer::update(float deltaTime){
		frameBuffer->bind();

		Renderer::clear();
		if(running){
			runtimeScene->updateRuntime(deltaTime);
		}else{
			if(sceneHierarchy.getDrawCamera()){
				scene->updateEditor(deltaTime);
			}else{
				if(mouseOnViewport){
					editorCamera.update(deltaTime);
				}
				scene->updateEditor(deltaTime, editorCamera.getCamera());
			}
		}
		
		frameBuffer->unbind();
	}
	void EditorLayer::imGuiRender(){
		//dockspace
		bool* open;
		static bool opt_fullscreen = true;
	    static bool opt_padding = false;
	    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	    // because it would be confusing to have two docking targets within each others.
	    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	    if (opt_fullscreen){
	        const ImGuiViewport* viewport = ImGui::GetMainViewport();
	        ImGui::SetNextWindowPos(viewport->WorkPos);
	        ImGui::SetNextWindowSize(viewport->WorkSize);
	        ImGui::SetNextWindowViewport(viewport->ID);
	        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	    }
	    else{
	        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	    }

	    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	    // and handle the pass-thru hole, so we ask Begin() to not render a background.
	    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
	        window_flags |= ImGuiWindowFlags_NoBackground;

	    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	    // all active windows docked into it will lose their parent and become undocked.
	    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	    if (!opt_padding)
	        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	    ImGui::Begin("DockSpace Demo", open, window_flags);
	    if (!opt_padding)
	        ImGui::PopStyleVar();

	    if (opt_fullscreen)
	        ImGui::PopStyleVar(2);

	    // Submit the DockSpace
	    ImGuiIO& io = ImGui::GetIO();
	    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable){
	        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	    }
	    if (ImGui::BeginMenuBar()){
	        if (ImGui::BeginMenu("File")){
				if(ImGui::MenuItem("New")){
					scene = std::make_shared<Scene>();
					serializer.setEnt(scene);
					sceneHierarchy.setContext(scene);
				}
				if(ImGui::MenuItem("Save")){
					if(explorerMode == 0){
						explorerMode = 1;
						explorer.reset(FileExplorerFlags_MakeFile);
					}
				}
				if(ImGui::MenuItem("Open")){
					if(explorerMode == 0){
						explorerMode = 2;
						explorer.reset(FileExplorerFlags_None);
					}
				}
				if(ImGui::MenuItem("Set Project Dir")){
					if(explorerMode == 0){
						explorerMode = 3;
						explorer.reset(FileExplorerFlags_DontShowFiles | FileExplorerFlags_AlwaysShowBack);
					}
				}
				if(ImGui::MenuItem("Settings")){
					showSettings = !showSettings;
				}
	            if(ImGui::MenuItem("Exit")){
					App::getInstance().close();
				}
	            ImGui::EndMenu();
	        }
			
			if (ImGui::BeginMenu("Edit")){
	            if(ImGui::MenuItem("Exit")){
					App::getInstance().close();
				};
	            ImGui::EndMenu();
	        }
			if (ImGui::BeginMenu("Help")){
	            if(ImGui::MenuItem("Exit")){
					App::getInstance().close();
				};
	            ImGui::EndMenu();
	        }
			if (ImGui::BeginMenu("DoThing.exe")){
	            if(ImGui::MenuItem("Exit")){
					App::getInstance().close();
				};
	            ImGui::EndMenu();
	        }
			if (ImGui::BeginMenu("Why are you here")){
	            if(ImGui::MenuItem("Exit")){
					App::getInstance().close();
				};
	            ImGui::EndMenu();
	        }
	        ImGui::EndMenuBar();
			
	    }
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0,0});
		ImGui::Begin("Viewport");
		mouseOnViewport = (ImGui::IsWindowFocused() && ImGui::IsWindowHovered());
		App::getInstance().getUiLayer()->setBlockEvents(!mouseOnViewport);
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		glm::vec2 glmSize = {viewportPanelSize.x, viewportPanelSize.y};
		if(viewportSize != glmSize){
			viewportSize = glmSize;
			frameBuffer->resize((int)viewportSize.x, (int)viewportSize.y);
			if(running){
				runtimeScene->viewportResize((int)viewportSize.x, (int)viewportSize.y);
			}else{
				scene->viewportResize((int)viewportSize.x, (int)viewportSize.y);
				editorCamera.setAspect(viewportSize.x / viewportSize.y);
			}
		}
		ImGui::Image((void*)frameBuffer->getColor(), ImVec2{viewportSize.x, viewportSize.y}, ImVec2{0,1}, ImVec2{1,0});
		if(ImGui::BeginDragDropTarget()){
			if(auto payload = ImGui::AcceptDragDropPayload("ContentBrowserItem")){
				const wchar_t* data = (wchar_t*)payload->Data;
				std::filesystem::path path = data;
				if(path.extension() == ".scene")
					openScene(data);
			}

		}
		ImGui::End();
		ImGui::PopStyleVar();
		sceneHierarchy.uiRender();
		contentBrowser.render();
		console.draw();
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 1.5 * SettingsPanel::scaleAllSizes));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
		ImGui::Begin("##toolbar", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
		if(!running){
			if(ImGui::Button("|>")){
				startRun();
			}
		}else{
			if(ImGui::Button("||")){
				stopRun();
			}
		}
		ImGui::SameLine();
		ImGui::MenuItem(("aspect: " + std::to_string((int)viewportSize.x) + " / " + std::to_string((int)viewportSize.y)).c_str());
		ImGui::End();
		ImGui::PopStyleVar(2);
		if(showSettings){
			settings.draw();
		}
	    ImGui::End();

		switch(explorerMode){
			case 0:
				break;
			case 1:
				if(int i = explorer.render(".scene")){
					if(i == 1){
						serializer.seralize(explorer.outPath.string());
					}
					explorerMode = 0;
				}
				break;
			case 2:
				if(int i = explorer.render(".scene")){
					if(i == 1){
						scene = std::make_shared<Scene>();
						serializer.setEnt(scene);
						sceneHierarchy.setContext(scene);
						serializer.deseralize(explorer.outPath.string());
					}
					explorerMode = 0;
				}
				break;
			case 3:
				if(int i = explorer.render("")){
					if(i == 1){
						std::string path = std::filesystem::absolute(explorer.outPath).string();
						contentBrowser.setMainPath(path);
						explorer.setMainPath(path);
					}
					explorerMode = 0;
				}
				break;
		}
	}
	void EditorLayer::event(Event* e){
		editorCamera.event(e);
	}
	void EditorLayer::openScene(const std::filesystem::path& path){
		if(running){
			stopRun();
		}
		scene = std::make_shared<Scene>();
		serializer.setEnt(scene);
		sceneHierarchy.setContext(scene);
		serializer.deseralize(path.string());
	}
	void EditorLayer::startRun(){
		running = true;
		runtimeScene = scene->copy();
		sceneHierarchy.setContext(runtimeScene);
		runtimeScene->viewportResize((int)viewportSize.x, (int)viewportSize.y);
	}
	void EditorLayer::stopRun(){
		runtimeScene->stop();
		running = false;
		runtimeScene = nullptr;
		sceneHierarchy.setContext(scene);
		scene->viewportResize((int)viewportSize.x, (int)viewportSize.y);
		editorCamera.setAspect(viewportSize.x / viewportSize.y);
	}
}