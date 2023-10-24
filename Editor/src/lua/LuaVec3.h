#include <lua/lua.hpp>
#include <string.h>
namespace Engine{
	class LuaVec3{
		public:
		static void make(lua_State* l, float* ptr){
			lua_newtable(l);
			int tablePos = lua_gettop(l);
			lua_pushlightuserdata(l, ptr);
			lua_setfield(l, tablePos, "id");
			lua_newtable(l);
			lua_pushcfunction(l, index);
			lua_setfield(l, -2, "__index");
			lua_pushcfunction(l, newIndex);
			lua_setfield(l, -2, "__newindex");
			lua_setmetatable(l, tablePos);
		}
		static int index(lua_State* l){
			lua_getfield(l, 1, "id");
			float* ptr = (float*)lua_touserdata(l, -1);
			const char* i = lua_tostring(l, 2);
			if(strcmp(i, "x")){
				lua_pushnumber(l, *ptr);
				return 1;
			}
			if(strcmp(i, "y")){
				lua_pushnumber(l, *(ptr + 1));
				return 1;
			}
			if(strcmp(i, "z")){
				lua_pushnumber(l, *(ptr + 2));
				return 1;
			}
		}
		static int newIndex(lua_State* l){
			lua_getfield(l, 1, "id");
			float* ptr = (float*)lua_touserdata(l, -1);
			const char* i = lua_tostring(l, 2);
			float val = lua_tonumber(l, 3);
			if(strcmp(i, "x")){
				*ptr = val;
			}
			if(strcmp(i, "y")){
				*(ptr + 1) = val;
			}
			if(strcmp(i, "z")){
				*(ptr + 2) = val;
			}
			return 0;
		}
	};
}