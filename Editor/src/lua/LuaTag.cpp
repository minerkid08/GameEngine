#include "LuaTag.h"

namespace Engine{
	int LuaTag::make(lua_State* l, const Entity& ent){
		lua_newtable(l);
		int transformPos = lua_gettop(l);

		lua_pushcfunction(l, setTag);
		lua_setfield(l, -2, "setTag");

		lua_pushcfunction(l, getTag);
		lua_setfield(l, -2, "getTag");

		lua_pushlightuserdata(l, (void*)(entt::entity)ent);
		lua_setfield(l, -2, "id");

		return transformPos;
	}
	static Components::Tag& getTagC(lua_State* l){
		lua_getglobal(l, "Entity");
		lua_getfield(l, -1, "id");
		Entity* ent = (Entity*)lua_touserdata(l, -1);
		lua_getfield(l, 1, "id");
		int id = (uint64_t)lua_touserdata(l, -1);
		return Entity(ent->getScene(), (entt::entity)id).getComp<Components::Tag>();
	}
	int LuaTag::getTag(lua_State* l){
		Components::Tag& tag = getTagC(l);
		lua_pushstring(l, tag.tag.c_str());
		return 1;
	}
	int LuaTag::setTag(lua_State* l){
		Components::Tag& tag = getTagC(l);
		const char* name = lua_tostring(l, 2);
		tag.tag = name;
		return 0;
	}
}