#pragma once
#include "Event.h"
#include <sstream>

namespace Engine{
	class KeyEvent : public Event{
		public:
		int keyCode;
		EventClassCategory(CatInput | CatKeyboard)
		KeyEvent(int code){
			keyCode = code;
		}
	};
	class KeyDownEvent : public KeyEvent{
		public:
		EventClassType(KeyPressed);
		KeyDownEvent(int code) : KeyEvent(code){}
		std::string toString(){
			std::stringstream ss;
			ss << "KeyDownEvent: " << keyCode;
			return ss.str();
		}
	};
	class KeyUpEvent : public KeyEvent{
		public:
		EventClassType(KeyReleased);
		KeyUpEvent(int code) : KeyEvent(code){}
		std::string toString(){
			std::stringstream ss;
			ss << "KeyUpEvent: " << keyCode;
			return ss.str();
		}
	};
}