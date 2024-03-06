#pragma once
#include <lua/lua.hpp>

namespace Engine{
	class LuaWorld{
		public:
		static void make(lua_State* l);
		static int getWindowWidth(lua_State* l);
		static int getWindowHeight(lua_State* l);
	};
}