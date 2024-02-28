#pragma once

#include <lua/lua.hpp>
#include <Scene/Entity.h>
namespace Engine{
	class LuaSpriteRenderer{
		public:
		static int make(lua_State* l, const Entity& ent);
		static int setTint(lua_State* l);
		static int getTint(lua_State* l);
		static int setTile(lua_State* l);
		static int getTile(lua_State* l);
		static int setUv(lua_State* l);
		static int getUv(lua_State* l);
		static int setTex(lua_State* l);
		static int getTex(lua_State* l);
		static int setMode(lua_State* l);
	};
}