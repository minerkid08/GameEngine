#include "LuaInput.h"
#include "Engine.h"

namespace Engine{
	void LuaInput::make(lua_State* l){
		lua_newtable(l);
		int pos = lua_gettop(l);
		lua_pushvalue(l, pos);
		lua_setglobal(l, "input");

		lua_pushcfunction(l, mouseButtonDown);
		lua_setfield(l, -2, "mouseButtonDown");
		
		lua_pushcfunction(l, mouseX);
		lua_setfield(l, -2, "mouseX");
		
		lua_pushcfunction(l, mouseY);
		lua_setfield(l, -2, "mouseY");
		
		lua_pushcfunction(l, keyDown);
		lua_setfield(l, -2, "keyDown");
	}
	int LuaInput::mouseButtonDown(lua_State* l){
		int button = lua_tointeger(l, 1);
		lua_pushboolean(l, Input::mouseDown(button));
		return 1;
	}
	int LuaInput::mouseX(lua_State* l){
		lua_pushnumber(l, Input::mouseX());
		return 1;
	}
	int LuaInput::mouseY(lua_State* l){
		lua_pushnumber(l, Input::mouseY());
		return 1;
	}
	int LuaInput::keyDown(lua_State* l){
		int button = lua_tointeger(l, 1);
		lua_pushboolean(l, Input::keyDown(button));
		return 1;
	}
}