#pragma once
#include "renderer/Camera.h"
#include "Core/Core.h"
#include "Events/AppEvent.h"
#include "Events/MouseEvent.h"
#include <glm/glm.hpp>
namespace Engine{
	class API CameraController{
		public:
		CameraController(float aspect);
		void update(float deltaTime);
		void event(Event* e);
		Camera& getCamera(){return cam;}
		float zoom = 1;
		private:
		bool mouseScroll(MouseScrollEvent* e);
		bool windowResize(WindowResizeEvent* e);
		float aspect;
		glm::vec2 pos;
		float moveSpeed = 1;
		Camera cam;
	};
}