#include "Window.h"
#include "Log.h"
#include "Events/AppEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
namespace Engine{
	Window::Window(unsigned int _width, unsigned int _height, std::string _title){
		data = new WindowData();
		data->width = _width;
		data->height = _height;
		data->title = _title;
		Log::Info("CreateWindow: " + data->title + ", (" + std::to_string(data->width) + ", " + std::to_string(data->height) + ")");
		if(!glfwInited){
			bool sucess = glfwInit();
			if(!sucess){
				Log::Error("Could not init glfw");
			}
			glfwSetErrorCallback(glfwErrorCallback);
			glfwInited = true;
		}

		window = glfwCreateWindow(data->width, data->height, data->title.c_str(), NULL, NULL);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, data);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if(!status){
			Log::Error("Could not init GLAD");
		}

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height){
			WindowData* a = (WindowData*)glfwGetWindowUserPointer(window);
			a->width = width;
			a->height = height;
			WindowResizeEvent e(width, height);
			a->callback(e);
		});
		glfwSetWindowCloseCallback(window, [](GLFWwindow* window){
			WindowData* a = (WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent e;
			a->callback(e);
		});
		glfwSetKeyCallback(window, [](GLFWwindow* window, int code, int scancode, int action, int mods){
			WindowData* a = (WindowData*)glfwGetWindowUserPointer(window);
			switch(action){
				case GLFW_PRESS:{
					KeyDownEvent e(code);
					a->callback(e);
					break;
				}
				case GLFW_RELEASE:
					{
					KeyUpEvent e(code);
					a->callback(e);
					break;
				}
			}
		});
		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods){
			WindowData* a = (WindowData*)glfwGetWindowUserPointer(window);
			switch(action){
				case GLFW_PRESS:{
					MouseButtonDownEvent e(button);
					a->callback(e);
					break;
				}
				case GLFW_RELEASE:
					{
					MouseButtonUpEvent e(button);
					a->callback(e);
					break;
				}
			}
		});
		glfwSetScrollCallback(window, [](GLFWwindow* window, double x, double y){
			WindowData* a = (WindowData*)glfwGetWindowUserPointer(window);
			MouseScrollEvent e((float)x,(float)y);
			a->callback(e);
		});
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y){
			WindowData* a = (WindowData*)glfwGetWindowUserPointer(window);
			MouseMoveEvent e((float)x,(float)y);
			a->callback(e);
		});
		glfwSetErrorCallback([](int code, const char* desc){
			Log::Error("GL error:" + std::to_string(code) + ", " + desc);
		});
	}
	Window::~Window(){

	}
	void Window::update(){
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	void Window::shutdown(){
		glfwDestroyWindow(window);
	}
	void Window::resize(int width, int height){
		data->width = width;
		data->height = height;
		glViewport(0, 0, width, height);
	}
	void Window::setHint(int hint, int value){
		glfwWindowHint(hint, value);
	}
}