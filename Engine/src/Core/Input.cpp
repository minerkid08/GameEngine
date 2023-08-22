#include "Input.h"
#include "App.h"
#include <glfw/glfw3.h>

namespace Engine{

	Input* Input::instance = new Input();

	bool Input::keyDownImpl(int key){
		GLFWwindow* window = App::getInstance().getWindow().getWindow();
		int state = glfwGetKey(window, key);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool Input::mouseDownImpl(int btn){
		GLFWwindow* window = App::getInstance().getWindow().getWindow();
		int state = glfwGetMouseButton(window, btn);
		return state == GLFW_PRESS;
	}
	float Input::mouseXImpl(){
		GLFWwindow* window = App::getInstance().getWindow().getWindow();
		double x = 0;
		double y = 0;
		glfwGetCursorPos(window, &x, &y);
		return (float)x;
	}
	float Input::mouseYImpl(){
		GLFWwindow* window = App::getInstance().getWindow().getWindow();
		double x = 0;
		double y = 0;
		glfwGetCursorPos(window, &x, &y);
		return (float)y;
	}
}