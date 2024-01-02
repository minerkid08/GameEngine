#pragma once
#include <lua/lua.hpp>
#include <Scene/ScriptableObject.h>
namespace Engine{
	class LuaTransform{
		public:
		static int make(lua_State* l, const Entity& transform);
		static int setPos(lua_State* l);
		static int getPos(lua_State* l);
		static int getRot(lua_State* l);
		static int setRot(lua_State* l);
		static int setScale(lua_State* l);
		static int getScale(lua_State* l);
	};
}