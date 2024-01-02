#include "LuaSpriteRenderer.h"

namespace Engine{
	int LuaSpriteRenderer::make(lua_State* l, const Entity& ent){
		lua_newtable(l);
		int spritePos = lua_gettop(l);

		lua_pushcfunction(l, getTint);
		lua_setfield(l, -2, "getTint");

		lua_pushcfunction(l, setTint);
		lua_setfield(l, -2, "setTint");

		lua_pushlightuserdata(l, (void*)(entt::entity)ent);
		lua_setfield(l, -2, "id");

		return spritePos;
	}

	#define getComp() lua_getglobal(l, "Entity");\
		lua_getfield(l, -1, "id");\
		Entity* ent = (Entity*)lua_touserdata(l, -1);\
		lua_getfield(l, 1, "id");\
		int id = (uint64_t)lua_touserdata(l, -1);\
		Components::SpriteRenderer& renderer = Entity(ent->getScene(), (entt::entity)id).getComp<Components::SpriteRenderer>()

	int LuaSpriteRenderer::getTint(lua_State* l){
		getComp();
		lua_newtable(l);
		lua_pushnumber(l, renderer.color.x);
		lua_setfield(l, -2, "r");
		lua_pushnumber(l, renderer.color.y);
		lua_setfield(l, -2, "g");
		lua_pushnumber(l, renderer.color.z);
		lua_setfield(l, -2, "b");
		lua_pushnumber(l, renderer.color.w);
		lua_setfield(l, -2, "a");
		return 1;
	}
	int LuaSpriteRenderer::setTint(lua_State* l){
		lua_getfield(l, 2, "r");
		float x = lua_tonumber(l, -1);
		lua_getfield(l, 2, "g");
		float y = lua_tonumber(l, -1);
		lua_getfield(l, 2, "b");
		float z = lua_tonumber(l, -1);
		lua_getfield(l, 2, "a");
		float w = lua_tonumber(l, -1);
		getComp();
		renderer.color = {x, y, z, w};
		return 0;
	}
}