#pragma once
#include "Core.h"
namespace Engine{
	class API Input{
		public:
		inline static bool keyDown(int key){return instance->keyDownImpl(key);}

		inline static bool mouseDown(int btn){return instance->mouseDownImpl(btn);}

		inline static float mouseX(){return instance->mouseXImpl();}
		inline static float mouseY(){return instance->mouseYImpl();}
		protected:
		virtual bool keyDownImpl(int key);
		virtual bool mouseDownImpl(int btn);
		virtual float mouseXImpl();
		virtual float mouseYImpl();
		private:
		static Input* instance;
	};
}