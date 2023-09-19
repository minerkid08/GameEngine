#include "2dLayer.h"
Layer2D::Layer2D() : Layer("e"), cameraController(1280.0f / 720.0f){}
void Layer2D::attach(){
	tex = std::make_shared<Engine::Texture2D>("Game/textures/tex2.png");
	spriteSheet = std::make_shared<Engine::Texture2D>("Game/textures/sheet.png");
	coal = std::make_shared<Engine::SubTex2D>(spriteSheet, glm::vec2(16, 16), glm::vec2(0, 0));
	stone = std::make_shared<Engine::SubTex2D>(spriteSheet, glm::vec2(16, 16), glm::vec2(0, 1));
	open = new bool(false);
	Engine::FrameBufferSpec spec;
	spec.width = 1280;
	spec.height = 720;
	frameBuffer = std::make_shared<Engine::FrameBuffer>(spec);
}
void Layer2D::detach(){

}
void Layer2D::update(float deltaTime){
	cameraController.update(deltaTime);
	frameBuffer->bind();
	Engine::Renderer::clear();
	Engine::Renderer2D::beginScene(cameraController.getCamera());
	transform.pos = {0.0f, 0.0f,-0.1};
	transform.scale = {1.0f,2.0f};
	transform.rot = 45.0f;
	Engine::Renderer2D::draw(transform, color);
	for(int x = -1; x < 2; x++){
		for(int y = -1; y < 2; y++){
			transform.pos = {x * 6.0f,y * 6.0f,-0.2};
			transform.scale = {6.0f,6.0f};
			transform.rot = 0.0f;
			Engine::Renderer2D::draw(transform, (x == 0 && y == 0 ? coal : stone), 1.0f);
		}
	}
	Engine::Renderer2D::endScene();
	frameBuffer->unbind();
}
void Layer2D::imGuiRender(){
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
            // Disabling fullscreen would allow the window to be moved to the front of other windows,
            // which we can't undo at the moment without finer window depth/z control.
            if(ImGui::MenuItem("Exit")){
				Engine::App::getInstance().close();
			};
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
	ImGui::Begin("E");
	ImGui::ColorPicker3("color", glm::value_ptr(color), ImGuiColorEditFlags_PickerHueWheel);
	ImGui::End();
	ImGui::Begin("Viewport");
	ImGui::Image((void*)frameBuffer->getColor(), ImVec2{1280.0f, 720.0f});
	ImGui::End();
    ImGui::End();
}
void Layer2D::event(Engine::Event* e){
	cameraController.event(e);
}