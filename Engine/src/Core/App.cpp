#include "App.h"
#include "Log.h"
#include "renderer/Renderer.h"
#include "renderer/2D/2DRenderer.h"
namespace Engine{
	App* App::instance = nullptr;
	App::App(){
		if(instance){
			Log::Error("App already exists");
			return;
		}
		window = uniqPtr<Window>(Window::MakeWindow(1280,720,"window.png"));
		window->setEventCallback(std::bind(App::event, this, std::placeholders::_1));
		Renderer::init();
		Renderer2D::init();
		instance = this;
		uiLayer = new ImGuiLayer();
		pushOverlay(uiLayer);
	}
	App::~App(){

	}
	void App::pushLayer(Layer* layer){
		layerStack.pushLayer(layer);
	}
	void App::pushOverlay(Layer* overlay){
		layerStack.pushOverlay(overlay);
	}
	void App::run(){
		Renderer::setClearColor({0.25f, 0.25f, 0.25f, 1.0f});
		while(running){
			Renderer::clear();
			
			float currentTime = (float)glfwGetTime();
			Time time = currentTime - lastDeltaTime;
			lastDeltaTime = currentTime;

			for(Layer* layer : layerStack){
				layer->update(time.getSec());
			}
			uiLayer->begin();
			for(Layer* layer : layerStack){
				layer->imGuiRender();
			}
			uiLayer->end();
			window->update();
		}
	}
	bool App::windowClose(WindowCloseEvent& e){
		running = false;
		return true;
	}
	bool App::windowResize(WindowResizeEvent& e){
		window->resize(e.width, e.height);
		return false;
	}
	void App::event(Event& e){
		EventDispatcher d(e);
		d.dispatch<WindowCloseEvent>(std::bind(App::windowClose, this, std::placeholders::_1));
		d.dispatch<WindowResizeEvent>(std::bind(App::windowResize, this, std::placeholders::_1));
		for(auto it = layerStack.end(); it != layerStack.begin(); ){
			(*--it)->event(e);
			if(e.isHandled()){
				break;
			}
		}
	}
}