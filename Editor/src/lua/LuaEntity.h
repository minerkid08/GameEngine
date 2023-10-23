#pragma once
#include <lua/lua.hpp>
#include <Engine.h>

namespace Engine{
	class LuaEntity{
		public:
		static void make(lua_State* l, Entity* ent);
		static int makeEnt(lua_State* l, const Entity& ent);
		
		static int createEnt(lua_State* l);
		static int getByEntName(lua_State* l);

		static int getComp(lua_State* l);
		static int addComp(lua_State* l);
		static int hasComp(lua_State* l);
		static int removeComp(lua_State* l);
	};
}