#include "2dLayer.h"
Layer2D::Layer2D() : Layer("e"), cameraController(1280.0f / 720.0f){}
void Layer2D::attach(){
	tex = std::make_shared<Engine::Texture2D>("Game/textures/tex2.png");
	tex2 = std::make_shared<Engine::Texture2D>("Game/textures/tex2.png");
}
void Layer2D::detach(){

}
void Layer2D::update(float deltaTime){
	cameraController.update(deltaTime);
}
void Layer2D::imGuiRender(){
	ImGui::Begin("E");
	ImGui::ColorPicker3("color", glm::value_ptr(color));
	ImGui::End();
	Engine::Renderer2D::beginScene(cameraController.getCamera());
	//Engine::Renderer2D::draw({0.0f,0.0f},{1.0f,1.0f},glm::vec4(color, 1.0f));
	Engine::Renderer2D::draw({0.0f,0.0f,-0.1},{2.0f,2.0f},glm::vec4(color, 1.0f));
	Engine::Renderer2D::draw({0.0f,0.0f,-0.2},{4.0f,4.0f},tex,glm::vec4(0.5f, 0.2f, 0.3f, 1.0f));
	Engine::Renderer2D::endScene();
}
void Layer2D::event(Engine::Event& e){
	cameraController.event(e);
}