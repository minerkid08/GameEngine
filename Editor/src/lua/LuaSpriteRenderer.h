#pragma once

#include <lua/lua.hpp>
#include <Scene/Entity.h>
namespace Engine{
	class LuaSpriteRenderer{
		public:
		static int make(lua_State* l, const Entity& ent);
		static int setTint(lua_State* l);
		static int getTint(lua_State* l);
	};
}