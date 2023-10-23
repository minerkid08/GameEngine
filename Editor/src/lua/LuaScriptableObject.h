#pragma once
#include <Engine.h>
#include <Scene/ScriptableObject.h>
#include <lua/lua.hpp>
#include "Panels/Console.h"
#include "LuaTransform.h"
#include "LuaInput.h"
#include "LuaKeyCodes.h"
#include "LuaEntity.h"
#include "LuaVec2.h"
namespace Engine{
	class LuaScriptableObject : public ScriptableObject{
		public:
		void compile(){
			if(l){
				lua_close(l);
				l = nullptr;
				state = false;
			}
			l = luaL_newstate();
			luaL_openlibs(l);
			lua_register(l, "info", info);
			lua_register(l, "warn", warn);
			lua_register(l, "error", error);

			LuaInput::make(l);
			LuaKeycode::make(l);
			LuaEntity::make(l, &ent);
			LuaVec2::make(l);

			int entPos = LuaEntity::makeEnt(l, ent);
			lua_pushvalue(l, entPos);
			lua_setglobal(l, "entity");

			state = checkState(luaL_dofile(l, path.c_str()));
		}
		~LuaScriptableObject(){
			if(l){
				lua_close(l);
				l = nullptr;
				state = false;
			}
		}
		void create(){
			if(state){
				lua_getglobal(l, "create");
				if(lua_isfunction(l, -1)){
					if(checkState(lua_pcall(l, 0, 0, 0))){
						return;
					}
				}
			}
		}
		void update(float deltaTime){
			if(state){
				lua_getglobal(l, "update");
				if(lua_isfunction(l, -1)){
					lua_pushnumber(l, deltaTime);
					if(checkState(lua_pcall(l, 1, 0, 0))){
						return;
					}
				}
			}
		}
		void destroy(){
			if(state){
				lua_getglobal(l, "destroy");
				if(lua_isfunction(l, -1)){
					if(checkState(lua_pcall(l, 0, 0, 0))){
						return;
					}
				}
				if(l){
					lua_close(l);
					l = nullptr;
					state = false;
				}
			}
		}

		static int info(lua_State* l){
			if(lua_isstring(l, 1)){
				const char* d = lua_tostring(l, 1);
				Console::add(d, 1);
			}
			return 0;
		}
		static int warn(lua_State* l){
			if(lua_isstring(l, 1)){
				const char* d = lua_tostring(l, 1);
				Console::add(d, 2);
			}
			return 0;
		}
		static int error(lua_State* l){
			if(lua_isstring(l, 1)){
				const char* d = lua_tostring(l, 1);
				Console::add(d, 3);
			}
			return 0;
		}
		private:
		lua_State* l = nullptr;
		bool checkState(int r){
			if(r != LUA_OK){
				Console::add(lua_tostring(l, -1), 3);
				return false;
			}
			return true;
		}
	};
}