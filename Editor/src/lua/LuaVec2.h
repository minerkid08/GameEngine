#pragma once
#include <lua/lua.hpp>

namespace Engine{
	class LuaVec2{
		public:
		static void make(lua_State* l);

		static int newVec2(lua_State* l);
		static int add(lua_State* l);
		static int sub(lua_State* l);
		static int mul(lua_State* l);
		static int div(lua_State* l);
		static int neg(lua_State* l);
		static int len(lua_State* l);
		static int dist(lua_State* l);
	};
}