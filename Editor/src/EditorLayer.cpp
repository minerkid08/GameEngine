#include "EditorLayer.h"
#include "Script.h"
namespace Engine{
	EditorLayer::EditorLayer() : Layer("e"){}
	void EditorLayer::attach(){
		scene = std::make_shared<Scene>();
		square = scene->createEnt();

		Components::Transform& transform = square.getComp<Components::Transform>();
		transform.pos = glm::vec3{0.0f, 0.0f, 0.0f};
		transform.scale = glm::vec2{1.0f, 1.0f};
		transform.rot = 0.0f;

		square.addComp<Components::SpriteRenderer>();
		
		camera = scene->createEnt("camera");
		camera.addComp<Components::Camera>(1280.0f / 720.0f, 1.0f);
		camera.addComp<Components::NativeScript>().bind<Script>();

		camera2 = scene->createEnt("camera2");
		camera2.addComp<Components::Camera>(1280.0f / 720.0f, 1.0f);
		camera2.getComp<Components::Transform>().pos = {0.5f, 0.5f, 0.0f};


		open = new bool(false);
		FrameBufferSpec spec;
		spec.width = 1280;
		spec.height = 720;
		frameBuffer = std::make_shared<FrameBuffer>(spec);
	}
	void EditorLayer::detach(){

	}
	void EditorLayer::update(float deltaTime){
		scene->update(deltaTime);
		
		frameBuffer->bind();

		Renderer::clear();
		square.getComp<Components::SpriteRenderer>().color = color;	
		scene->update(deltaTime);
		
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
	            if(ImGui::MenuItem("Exit")){
					App::getInstance().close();
				};
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
		ImGui::Begin("E");
		ImGui::ColorPicker3("color", glm::value_ptr(color), ImGuiColorEditFlags_PickerHueWheel);

		ImGui::Checkbox("camera1", &camera.getComp<Components::Camera>().mainCamera);
		ImGui::Checkbox("camera2", &camera2.getComp<Components::Camera>().mainCamera);
		
		ImGui::End();
		
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0,0});
		ImGui::Begin("Viewport");
		App::getInstance().getUiLayer()->setBlockEvents(!(ImGui::IsWindowFocused() && ImGui::IsWindowHovered()));
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if(viewportSize != *((glm::vec2*)&viewportPanelSize)){
			viewportSize = {ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y};
			frameBuffer->resize((int)viewportSize.x, (int)viewportSize.y);
			scene->viewportResize((int)viewportSize.x, (int)viewportSize.y, 1.0f);
		}
		ImGui::Image((void*)frameBuffer->getColor(), ImVec2{viewportSize.x, viewportSize.y});
		ImGui::End();
		ImGui::PopStyleVar();
	    ImGui::End();
	}
	void EditorLayer::event(Event* e){
	}
}