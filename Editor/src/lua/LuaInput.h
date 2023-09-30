#pragma once

#include <lua/lua.hpp>

namespace Engine{
	class LuaInput{
		public:
		static void make(lua_State* l);
		static int mouseButtonDown(lua_State* l);
		static int mouseX(lua_State* l);
		static int mouseY(lua_State* l);
		static int keyDown(lua_State* l);
	};
}