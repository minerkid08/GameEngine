#pragma once
#include <lua/lua.hpp>
#include <Scene/ScriptableObject.h>
namespace Engine{
	class LuaTransform{
		public:
		static int make(lua_State* l, const Entity& transform);
		static int getPosX(lua_State* l);
		static int setPosX(lua_State* l);
		static int getPosY(lua_State* l);
		static int setPosY(lua_State* l);
		static int getPosZ(lua_State* l);
		static int setPosZ(lua_State* l);
		static int getRot(lua_State* l);
		static int setRot(lua_State* l);
		static int getScaleX(lua_State* l);
		static int setScaleX(lua_State* l);
		static int getScaleY(lua_State* l);
		static int setScaleY(lua_State* l);
	};
}