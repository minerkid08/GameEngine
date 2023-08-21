#include <Engine.h>
class ExLayer : public Engine::Layer{
	public:
	ExLayer() : Layer("layerNaem"){
		mesh = Engine::Mesh::Plane(Engine::Material::MakeSolidColor({0.7, 0.3, 0.4}));
		mesh2 = Engine::Mesh::Plane(Engine::Material::MakeTexture("Game/textures/tex3.png"));
	}

	void imGuiRender() override {
		ImGui::Begin("Camera");
		ImGui::SliderFloat("X", &x, -5.0f, 5.0f);
		ImGui::SliderFloat("Y", &y, -5.0f, 5.0f);
		ImGui::SliderFloat("Rot", &r, 0.0f, 360.0f);
		ImGui::End();
	}

	void update(float deltaTime){
		Engine::App::getInstance().cam.setPos(glm::vec3(x,y,0.0f));
		Engine::App::getInstance().cam.setRot(r);
		Engine::Renderer::submit(mesh, 0);
		Engine::Renderer::submit(mesh2, 1);
	}

	void event(Engine::Event& event) override{}
	private:
	Engine::shdPtr<Engine::Mesh> mesh;
	Engine::shdPtr<Engine::Mesh> mesh2;
	float x = 0;
	float y = 0;
	float r = 0;
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