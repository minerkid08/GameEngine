#pragma once
#include "Core.h"
#include "Events/AppEvent.h"
#include "Log.h"
#include "Core/Time.h"
#include "Window.h"
#include "LayerStack.h"
#include "ImGuiLayer.h"
#include "renderer/Shader.h"
#include "renderer/Buffer.h"
#include "renderer/VertArray.h"
#include "renderer/Camera.h"
#include <memory>
namespace Engine{
	class API App{
		public:
		App();
		~App();
		void run();
		void event(Event& e);
		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		inline Window& getWindow(){return *window;}
		static inline App& getInstance(){return *instance;}

		Camera cam;
		private:
		static App* instance;
		bool windowClose(WindowCloseEvent& e);
		uniqPtr<Window> window;
		ImGuiLayer* uiLayer;
		bool running = true;
		LayerStack layerStack;

		float lastDeltaTime = 0.0f;
	};
	App* createApp();
}