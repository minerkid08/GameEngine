#include "LuaVec2.h"
#include <math.h>

namespace Engine{
	void LuaVec2::make(lua_State* l){
		lua_newtable(l);
		int pos = lua_gettop(l);

		lua_pushcfunction(l, newVec2);
		lua_setfield(l, -2, "new");

		lua_pushcfunction(l, add);
		lua_setfield(l, -2, "add");

		lua_pushcfunction(l, sub);
		lua_setfield(l, -2, "sub");

		lua_pushcfunction(l, mul);
		lua_setfield(l, -2, "mul");

		lua_pushcfunction(l, div);
		lua_setfield(l, -2, "div");

		lua_pushcfunction(l, neg);
		lua_setfield(l, -2, "neg");

		lua_pushcfunction(l, len);
		lua_setfield(l, -2, "len");

		lua_pushcfunction(l, dist);
		lua_setfield(l, -2, "dist");

		lua_setglobal(l, "Vec2");
	}
	int LuaVec2::newVec2(lua_State* l){
		int argCount = lua_gettop(l);
		switch (argCount){
		case 0:
			lua_newtable(l);
			lua_pushnumber(l, 0);
			lua_setfield(l, -2, "x");
			lua_pushnumber(l, 0);
			lua_setfield(l, -2, "y");
			return 1;
		case 1:
			lua_newtable(l);
			lua_pushvalue(l, 1);
			lua_setfield(l, -2, "x");
			lua_pushvalue(l, 1);
			lua_setfield(l, -2, "y");
			return 1;
		case 2:
			lua_newtable(l);
			lua_pushvalue(l, 1);
			lua_setfield(l, -2, "x");
			lua_pushvalue(l, 2);
			lua_setfield(l, -2, "y");
			return 1;
		default:
			return 0;
		}
	}
	#define getValue() lua_getfield(l, 1, "x");\
		float x = lua_tonumber(l, -1);\
		lua_getfield(l, 1, "y");\
		float y = lua_tonumber(l, -1);

	#define getValues() lua_getfield(l, 1, "x");\
		float x = lua_tonumber(l, -1);\
		lua_getfield(l, 1, "y");\
		float y = lua_tonumber(l, -1);\
		lua_getfield(l, 2, "x");\
		float x2 = lua_tonumber(l, -1);\
		lua_getfield(l, 2, "y");\
		float y2 = lua_tonumber(l, -1);
	
	#define newtable() lua_newtable(l);\
		lua_pushnumber(l, x);\
		lua_setfield(l, -2, "x");\
		lua_pushnumber(l, y);\
		lua_setfield(l, -2, "y");\

	int LuaVec2::add(lua_State* l){
		if(lua_istable(l, 2)){
			getValues();
			x = x + x2;
			y = y + y2;
			newtable();
		}else{
			getValue();
			float i = lua_tonumber(l, 2);
			x = x + i;
			y = y + i;
			newtable();
		}
		return 1;
	}
	int LuaVec2::sub(lua_State* l){
		if(lua_istable(l, 2)){
			getValues();
			x = x - x2;
			y = y - y2;
			newtable();
		}else{
			getValue();
			float i = lua_tonumber(l, 2);
			x = x - i;
			y = y - i;
			newtable();
		}
		return 1;
	}
	int LuaVec2::mul(lua_State* l){
		if(lua_istable(l, 2)){
			getValues();
			x = x * x2;
			y = y * y2;
			newtable();
		}else{
			getValue();
			float i = lua_tonumber(l, 2);
			x = x * i;
			y = y * i;
			newtable();
		}
		return 1;
	}
	int LuaVec2::div(lua_State* l){
		if(lua_istable(l, 2)){
			getValues();
			x = x / x2;
			y = y / y2;
			newtable();
		}else{
			getValue();
			float i = lua_tonumber(l, 2);
			x = x / i;
			y = y / i;
			newtable();
		}
		return 1;
	}
	int LuaVec2::neg(lua_State* l){
		getValue();
		x = -x;
		y = -y;
		newtable();
		return 1;
	}
	int LuaVec2::len(lua_State* l){
		getValue();
		float a = sqrtf(x * x + y * y);
		return 1;
	}
	int LuaVec2::dist(lua_State* l){
		getValues();
		float a = sqrtf(powf(x2 - x, 2) + pow(y2 - y, 2));
		lua_pushnumber(l, a);
		return 1;
	}
}