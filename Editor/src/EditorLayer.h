#pragma once
#include <Engine.h>
#include "Scene/Seralizer.h"
#include "Panels/SceneHierarchy.h"
namespace Engine{
	class EditorLayer : public Layer{
		public:
		EditorLayer();
		~EditorLayer();
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
		shdPtr<Scene> scene;

		Serializer serializer;

		char savePath[256];
		bool saveLoad = false;
		
		SceneHierarchy sceneHierarchy;
	};
}