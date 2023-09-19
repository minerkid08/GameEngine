#pragma once
#include <Engine.h>

class Layer2D : public Engine::Layer{
	public:
	Layer2D();
	void attach();
	void detach();
	void update(float deltaTime);
	void imGuiRender();
	void event(Engine::Event* e);
	private:
	bool* open;
	Engine::CameraController cameraController;
	glm::vec4 color = {0.5f, 0.5f, 0.5f, 1.0f};
	Engine::Transform transform;
	Engine::shdPtr<Engine::Texture2D> tex;
	Engine::shdPtr<Engine::Texture2D> spriteSheet;
	Engine::shdPtr<Engine::SubTex2D> coal;
	Engine::shdPtr<Engine::SubTex2D> stone;
	Engine::shdPtr<Engine::FrameBuffer> frameBuffer;
};