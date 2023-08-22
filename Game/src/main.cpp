#include <Engine.h>
class ExLayer : public Engine::Layer{
	public:
	ExLayer() : Layer("layerNaem"), camera(1280.0f/720.0f){
		mesh = Engine::Mesh::Plane(Engine::Material::MakeSolidColor(color));
		mesh->setPos({0.0f,0.0f,0.0f});
		mesh2 = Engine::Mesh::Plane(Engine::Material::MakeTexture("Game/textures/tex3.png"));
		mesh2->setPos({0.0f,0.0f,0.0f});
	}

	void imGuiRender() override {
		ImGui::Begin("Camera");
		ImGui::ColorPicker3("Color", glm::value_ptr(color));
		ImGui::End();
	}

	void update(float deltaTime){
		mesh->getMaterial()->setColor(color);
		camera.update(deltaTime);
		Engine::Renderer::beginScene(camera.getCamera());
		Engine::Renderer::submit(mesh, 0);
		Engine::Renderer::submit(mesh2, 1);
		Engine::Renderer::endScene();;
	}

	void event(Engine::Event& event) override{
		camera.event(event);
	}
	private:
	Engine::shdPtr<Engine::Mesh> mesh;
	Engine::shdPtr<Engine::Mesh> mesh2;
	glm::vec3 color = {0.7, 0.3, 0.4};
	Engine::CameraController camera;
};
class Sandbox : public Engine::App{
	public:
	Sandbox() : App(){
		pushLayer(new ExLayer());
	}
	~Sandbox(){

	}
};
Engine::App* Engine::createApp(){
	return new Sandbox();
}