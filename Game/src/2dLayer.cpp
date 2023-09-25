#include "2dLayer.h"
Layer2D::Layer2D() : Layer("e"), cameraController(1280.0f / 720.0f){}
void Layer2D::attach(){
	tex = std::make_shared<Engine::Texture2D>("Game/textures/tex2.png");
	spriteSheet = std::make_shared<Engine::Texture2D>("Game/textures/sheet.png");
	coal = std::make_shared<Engine::SubTex2D>(spriteSheet, glm::vec2(16, 16), glm::vec2(0, 0));
	stone = std::make_shared<Engine::SubTex2D>(spriteSheet, glm::vec2(16, 16), glm::vec2(0, 1));
	open = new bool(false);
}
void Layer2D::detach(){

}
void Layer2D::update(float deltaTime){
	cameraController.update(deltaTime);
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
}
void Layer2D::imGuiRender(){
	ImGui::Begin("E");
	ImGui::ColorPicker3("color", glm::value_ptr(color), ImGuiColorEditFlags_PickerHueWheel);
	ImGui::End();
}
void Layer2D::event(Engine::Event* e){
	cameraController.event(e);
}