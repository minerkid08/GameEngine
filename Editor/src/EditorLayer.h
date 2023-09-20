#pragma once
#include <Engine.h>
namespace Engine{
	class EditorLayer : public Layer{
		public:
		EditorLayer();
		void attach();
		void detach();
		void update(float deltaTime);
		void imGuiRender();
		void event(Event* e);
		private:
		bool* open;
		glm::vec2 viewportSize;
		Transform transform;
		shdPtr<FrameBuffer> frameBuffer;


		CameraController cameraController;
		glm::vec4 color = {0.5f, 0.5f, 0.5f, 1.0f};
		shdPtr<Texture2D> tex;
		shdPtr<Texture2D> spriteSheet;
		shdPtr<SubTex2D> coal;
		shdPtr<SubTex2D> stone;
	};
}