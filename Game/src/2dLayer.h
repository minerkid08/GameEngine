#pragma once
#include <Engine.h>

class Layer2D : public Engine::Layer{
	public:
	Layer2D();
	void attach();
	void detach();
	void update(float deltaTime);
	void imGuiRender();
	void event(Engine::Event& e);
	private:
	Engine::CameraController cameraController;
	glm::vec3 color;
};