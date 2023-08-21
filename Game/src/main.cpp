#include <Engine.h>
class ExLayer : public Engine::Layer{
	public:
	ExLayer() : Layer("layerNaem"){
		mesh = Engine::Mesh::Plane(Engine::Material::MakeSolidColor(color));
		mesh->setPos({0.0f,0.0f,-5.0f});
		mesh2 = Engine::Mesh::Plane(Engine::Material::MakeTexture("Game/textures/tex3.png"));
		mesh2->setPos({0.0f,0.0f,-5.0f});
		Engine::App::getInstance().cam.orthographic(-1.6f, 1.6f, 0.9f, -0.9f);
		//TODO: fix 3d
		//Engine::App::getInstance().cam.perspective(Engine::App::getInstance().getWindow().getWidth()/Engine::App::getInstance().getWindow().getHeight(), 45.0f, 0.1f, 100.0f);
	}

	void imGuiRender() override {
		ImGui::Begin("Camera");
		ImGui::SliderFloat("X", &x, -5.0f, 5.0f);
		ImGui::SliderFloat("Y", &y, -5.0f, 5.0f);
		ImGui::SliderFloat("Z", &z, -5.0f, 5.0f);
		ImGui::SliderFloat("Rot", &r, 0.0f, 360.0f);
		ImGui::ColorPicker3("Color", glm::value_ptr(color));
		ImGui::End();
	}

	void update(float deltaTime){
		Engine::App::getInstance().cam.setPos(glm::vec3(x,y,z));
		Engine::App::getInstance().cam.setRot(r);
		mesh->getMaterial()->setColor(color);
		Engine::Renderer::submit(mesh, 0);
		Engine::Renderer::submit(mesh2, 1);
	}

	void event(Engine::Event& event) override{}
	private:
	Engine::shdPtr<Engine::Mesh> mesh;
	Engine::shdPtr<Engine::Mesh> mesh2;
	float x = 0;
	float y = 0;
	float z = 0;
	float r = 0;
	glm::vec3 color = {0.7, 0.3, 0.4};
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