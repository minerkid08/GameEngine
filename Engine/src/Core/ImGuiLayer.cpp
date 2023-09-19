#include "ImGuiLayer.h"
#include "App.h"

#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glfw/glfw3.h>

namespace Engine{
	void ImGuiLayer::attach(){
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO();

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].x -1.0f;
		io.FontGlobalScale = 2.0f;
		style.ScaleAllSizes(2);

		ImGui_ImplGlfw_InitForOpenGL(App::getInstance().getWindow().getWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}
	void ImGuiLayer::detach(){
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
	void ImGuiLayer::update(float deltaTime){}
	void ImGuiLayer::begin(){
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
	}
	void ImGuiLayer::end(){
		ImGuiIO& io = ImGui::GetIO();
		Window& window = App::getInstance().getWindow();
		io.DisplaySize = ImVec2(window.getWidth(), window.getHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable){
			GLFWwindow* ctx = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(ctx);
		}
	}
	void ImGuiLayer::imGuiRender(){
		//static bool show = true;
		//ImGui::ShowDemoWindow(&show);
	}
}