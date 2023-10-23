#pragma once
#include <lua/lua.hpp>
#include <Engine.h>

namespace Engine{
	class LuaTag{
		public:
		static int make(lua_State* l, const Entity& ent);

		static int getTag(lua_State* l);
		static int setTag(lua_State* l);
	};
}