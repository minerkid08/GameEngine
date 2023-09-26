#pragma once
#include <Engine.h>
#include "Scene/Seralizer.h"
#include "Panels/SceneHierarchy.h"
#include "Panels/ContnentBrowser.h"
#include "Panels/FileExplorer.h"
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
		bool mouseOnViewport = false;
		bool saving = false;
		bool loading = false;
		CameraController editorCamera;
		SceneHierarchy sceneHierarchy;
		ContentBrowser contentBrowser;

		FileExplorer explorer;

		void openScene(const std::filesystem::path& path);
	};
}