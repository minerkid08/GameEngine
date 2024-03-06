#include "LuaWorld.h"
#include <EditorLayer.h>

namespace Engine{
	void LuaWorld::make(lua_State* l){
		lua_newtable(l);
		lua_pushcfunction(l, getWindowHeight);
		lua_setfield(l, -2, "getWindowHeight");
		lua_pushcfunction(l, getWindowWidth);
		lua_setfield(l, -2, "getWindowWidth");
		lua_setglobal(l, "World");
	}
	int LuaWorld::getWindowHeight(lua_State* l){
		lua_pushnumber(l, EditorLayer::viewportSize.y);
		return 1;		
	}
	int LuaWorld::getWindowWidth(lua_State* l){
		lua_pushnumber(l, EditorLayer::viewportSize.x);
		return 1;		
	}
}