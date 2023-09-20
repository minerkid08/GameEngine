#pragma once
#include "Core/Core.h"
#include "Core/Log.h"
#include <functional>
#include <string>
namespace Engine{
	enum EventType{
		None = 0,
		WindowClosed, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonRelased, MouseMoved, MouseScrolled
	};
	enum EventCategory{
		CatApplication = 1,
		CatInput = 2,
		CatKeyboard = 4,
		CatMouse = 8,
		CatMouseButton = 16
	};
	#define EventClassType(type) static int getStaticType() {return EventType::type;}\
		virtual int getType() override {return EventType::type;}\
		virtual const char* getName() override {return #type;}	

	#define EventClassCategory(category) virtual int getFlags() override {return category;}
	class Event{
		friend class EventDispatcher;
		public:
		Event(){}
		virtual int getType(){return 0;}
		virtual const char* getName(){return "0";}
		virtual int getFlags(){return 0;}
		virtual std::string toString(){return getName();}
		inline bool isHandled(){return handled;}
		inline bool isInCategory(int _category){
			return getFlags() & _category;
		}
		bool handled = false;
		private:
	}; 
	class EventDispatcher{
		public:
		template<typename T> using fn = std::function<bool(T*)>;
		EventDispatcher(Event* _event) : event(_event){}
		template<typename T>
		bool dispatch(fn<T> func){
			if(event->getType() == T::getStaticType()){
				event->handled |= func((T*)event);
				return true;
			}
			return false;
		}
		private:
		Event* event;
	};
}