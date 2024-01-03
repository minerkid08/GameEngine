#pragma once
#include <Engine.h>
#include "Seralizer.h"
#include "AssetManager.h"
#include "Panels/SceneHierarchy.h"
#include "Panels/ContnentBrowser.h"
#include "Panels/FileExplorer.h"
#include "Panels/Console.h"
#include "Panels/Settings.h"
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
		bool running = false;
		private:
		bool* open;
		glm::vec2 viewportSize;
		shdPtr<FrameBuffer> frameBuffer;
		shdPtr<Scene> scene;
		shdPtr<Scene> runtimeScene;
		shdPtr<AssetManager> assetManager;

		Serializer serializer;
		bool mouseOnViewport = false;
		int explorerMode = 0;
		bool showSettings = false;

		CameraController editorCamera;

		SceneHierarchy sceneHierarchy;
		ContentBrowser contentBrowser;
		Console console;
		SettingsPanel settings;
		FileExplorer explorer;

		void openScene(const std::filesystem::path& path);

		void startRun();
		void stopRun();
	};
}