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
		App(const char* title);
		App(int width, int height, const char* title);
		~App();
		void run();
		void event(Event& e);
		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void close();
		inline Window& getWindow(){return *window;}
		static inline App& getInstance(){return *instance;}

		private:
		static App* instance;
		bool windowClose(WindowCloseEvent* e);
		bool windowResize(WindowResizeEvent* e);
		uniqPtr<Window> window;
		ImGuiLayer* uiLayer;
		bool running = true;
		LayerStack layerStack;

		float lastDeltaTime = 0.0f;
	};
	App* createApp();
}