#include "LuaTransform.h"
namespace Engine{
	int LuaTransform::make(lua_State* l, const Entity& ent){
		lua_newtable(l);
		int transformPos = lua_gettop(l);

		lua_pushcfunction(l, getPos);
		lua_setfield(l, -2, "getPos");

		lua_pushcfunction(l, setPos);
		lua_setfield(l, -2, "setPos");

		lua_pushcfunction(l, getRot);
		lua_setfield(l, -2, "getRot");

		lua_pushcfunction(l, setRot);
		lua_setfield(l, -2, "setRot");

		lua_pushcfunction(l, getScale);
		lua_setfield(l, -2, "getScale");

		lua_pushcfunction(l, setScale);
		lua_setfield(l, -2, "setScale");

		lua_pushlightuserdata(l, (void*)(entt::entity)ent);
		lua_setfield(l, -2, "id");

		return transformPos;
	}
	static Components::Transform& getTransform(lua_State* l){
		lua_getglobal(l, "Entity");
		lua_getfield(l, -1, "id");
		Entity* ent = (Entity*)lua_touserdata(l, -1);
		lua_getfield(l, 1, "id");
		int id = (uint64_t)lua_touserdata(l, -1);
		return Entity(ent->getScene(), (entt::entity)id).getComp<Components::Transform>();
	}
	int LuaTransform::setPos(lua_State* l){
		lua_getfield(l, 2, "x");
		float x = lua_tonumber(l, -1);
		lua_getfield(l, 2, "y");
		float y = lua_tonumber(l, -1);
		lua_getfield(l, 2, "z");
		float z = lua_tonumber(l, -1);
		getTransform(l).pos = {x, y, z};
		return 0;
	}
	int LuaTransform::getPos(lua_State* l){
		Components::Transform& transform = getTransform(l);
		lua_newtable(l);
		lua_pushnumber(l, transform.pos.x);
		lua_setfield(l, -2, "x");
		lua_pushnumber(l, transform.pos.y);
		lua_setfield(l, -2, "y");
		lua_pushnumber(l, transform.pos.z);
		lua_setfield(l, -2, "z");
		return 1;
	}
	int LuaTransform::getRot(lua_State* l){
		lua_pushnumber(l, getTransform(l).rot);
		return 1;
	}
	int LuaTransform::setRot(lua_State* l){
		getTransform(l).rot = lua_tonumber(l, 2);
		return 0;
	}
	int LuaTransform::setScale(lua_State* l){
		lua_getfield(l, 2, "x");
		float x = lua_tonumber(l, -1);
		lua_getfield(l, 2, "y");
		float y = lua_tonumber(l, -1);
		getTransform(l).scale = {x, y};
		return 0;
	}
	int LuaTransform::getScale(lua_State* l){
		Components::Transform& transform = getTransform(l);
		lua_newtable(l);
		lua_pushnumber(l, transform.scale.x);
		lua_setfield(l, -2, "x");
		lua_pushnumber(l, transform.scale.y);
		lua_setfield(l, -2, "y");
		return 1;
	}
}