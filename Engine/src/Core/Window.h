#pragma once
#include "Events/Event.h"
#include "Core.h"
#include "Log.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace Engine{
	class Window{
		public:
		using EventCallbackFn = std::function<void(Event&)>;
		Window(unsigned int width, unsigned int height, std::string title);
		~Window();
		void update();
		void shutdown();
		unsigned int getWidth(){return data->width;}
		unsigned int getHeight(){return data->height;}

		void setEventCallback(const EventCallbackFn& fn){data->callback = fn;}

		GLFWwindow* getWindow(){return window;}

		static void glfwErrorCallback(int error, const char* desc){
			Log::Error("GLFW error: " + std::to_string(error) + ", " + desc);
		}

		static Window* MakeWindow(unsigned int width, unsigned int height, std::string title){
			return new Window(width, height, title);
		}
		void resize(int width, int height);
		private:
		struct WindowData{
			std::string title;
			unsigned int width;
			unsigned int height;
			EventCallbackFn callback;
		};
		WindowData* data;
		GLFWwindow* window;
		bool glfwInited;
	};
}