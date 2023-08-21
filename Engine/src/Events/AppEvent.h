#pragma once
#include "Event.h"
#include <sstream>

namespace Engine{
	class WindowResizeEvent : public Event{
		public:
		EventClassCategory(CatApplication)
		EventClassType(WindowResize)
		WindowResizeEvent(unsigned int _width, unsigned int _height){
			width = _width;
			height = _height;
		}
		std::string toString(){
			std::stringstream ss;
			ss << "WindowResizeEvent: " << width << "," << height;
			return ss.str();
		}
		unsigned int width;
		unsigned int height;
	};
	class WindowCloseEvent : public Event{
		public:
		EventClassCategory(CatApplication)
		EventClassType(WindowClosed)
		std::string toString(){
			std::stringstream ss;
			ss << "WindowCloseEvent";
			return ss.str();
		}
	};
}