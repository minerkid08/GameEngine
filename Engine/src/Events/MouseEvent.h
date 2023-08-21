#pragma once
#include "Event.h"
#include <sstream>

namespace Engine{
	class MouseMoveEvent : public Event{
		public:
		float x;
		float y;
		EventClassType(MouseMoved)
		EventClassCategory(CatInput | CatMouse)
		MouseMoveEvent(float _x, float _y){
			x = _x;
			y = _y;
		}
		std::string toString(){
			std::stringstream ss;
			ss << "MouseMoveEvent: " << x << "," << y;
			return ss.str();
		}
	};
	class MouseScrollEvent : public Event{
		public:
		float x;
		float y;
		EventClassType(MouseScrolled)
		EventClassCategory(CatInput | CatMouse)
		MouseScrollEvent(float _x, float _y){
			x = _x;
			y = _y;
		}
		std::string toString(){
			std::stringstream ss;
			ss << "MouseScrollEvent: " << x << "," << y;
			return ss.str();
		}
	};
	class MouseButtonEvent : public Event{
		public:
		int button;
		EventClassCategory(CatInput | CatMouse | CatMouseButton)
		MouseButtonEvent(int _button){
			button = _button;
		}
	};
	class MouseButtonDownEvent : public MouseButtonEvent{
		public:
		EventClassType(MouseButtonPressed)
		MouseButtonDownEvent(int _button) : MouseButtonEvent(_button){}
		std::string toString(){
			std::stringstream ss;
			ss << "MouseButtonDownEvent: " << button;
			return ss.str();
		}
	};
	class MouseButtonUpEvent : public MouseButtonEvent{
		public:
		EventClassType(MouseButtonRelased)
		MouseButtonUpEvent(int _button) : MouseButtonEvent(_button){}
		std::string toString(){
			std::stringstream ss;
			ss << "MouseButtonUpEvent: " << button;
			return ss.str();
		}
	};
}