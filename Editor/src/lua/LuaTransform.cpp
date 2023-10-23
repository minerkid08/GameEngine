#include "LuaTransform.h"
namespace Engine{
	int LuaTransform::make(lua_State* l, const Entity& ent){
		//pos table 
		lua_newtable(l);
		int posPos = lua_gettop(l);

		lua_pushcfunction(l, getPosX);
		lua_setfield(l, -2, "getX");

		lua_pushcfunction(l, getPosY);
		lua_setfield(l, -2, "getY");

		lua_pushcfunction(l, getPosZ);
		lua_setfield(l, -2, "getZ");

		lua_pushcfunction(l, setPosX);
		lua_setfield(l, -2, "setX");

		lua_pushcfunction(l, setPosY);
		lua_setfield(l, -2, "setY");

		lua_pushcfunction(l, setPosZ);
		lua_setfield(l, -2, "setZ");

		lua_pushlightuserdata(l, (void*)(entt::entity)ent);
		lua_setfield(l, -2, "id");

		//scale table
		lua_newtable(l);
		int scalePos = lua_gettop(l);

		lua_pushcfunction(l, getScaleX);
		lua_setfield(l, -2, "getX");

		lua_pushcfunction(l, getScaleY);
		lua_setfield(l, -2, "getY");

		lua_pushcfunction(l, setScaleX);
		lua_setfield(l, -2, "setX");

		lua_pushcfunction(l, setScaleY);
		lua_setfield(l, -2, "setY");

		lua_pushlightuserdata(l, (void*)(entt::entity)ent);
		lua_setfield(l, -2, "id");

		//transform table
		lua_newtable(l);
		int transformPos = lua_gettop(l);

		lua_pushvalue(l, posPos);
		lua_setfield(l, transformPos, "pos");

		lua_pushvalue(l, scalePos);
		lua_setfield(l, transformPos, "scale");

		lua_pushcfunction(l, getRot);
		lua_setfield(l, -2, "getRot");

		lua_pushcfunction(l, setRot);
		lua_setfield(l, -2, "setRot");

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
	int LuaTransform::getPosX(lua_State* l){
		lua_pushnumber(l, getTransform(l).pos.x);
		return 1;
	}
	int LuaTransform::getPosY(lua_State* l){
		lua_pushnumber(l, getTransform(l).pos.y);
		return 1;
	}
	int LuaTransform::getPosZ(lua_State* l){
		lua_pushnumber(l, getTransform(l).pos.z);
		return 1;
	}
	int LuaTransform::setPosX(lua_State* l){
		getTransform(l).pos.x = lua_tonumber(l, 2);
		return 0;
	}
	int LuaTransform::setPosY(lua_State* l){
		getTransform(l).pos.y = lua_tonumber(l, 2);
		return 0;
	}
	int LuaTransform::setPosZ(lua_State* l){
		getTransform(l).pos.z = lua_tonumber(l, 2);
		return 0;
	}
	int LuaTransform::getRot(lua_State* l){
		lua_pushnumber(l, getTransform(l).rot);
		return 1;
	}
	int LuaTransform::setRot(lua_State* l){
		getTransform(l).rot = lua_tonumber(l, 2);
		return 0;
	}
	int LuaTransform::getScaleX(lua_State* l){
		lua_pushnumber(l, getTransform(l).scale.x);
		return 1;
	}
	int LuaTransform::setScaleX(lua_State* l){
		getTransform(l).scale.x = lua_tonumber(l, 2);
		return 0;
	}
	int LuaTransform::getScaleY(lua_State* l){
		lua_pushnumber(l, getTransform(l).scale.y);
		return 1;
	}
	int LuaTransform::setScaleY(lua_State* l){
		getTransform(l).scale.y = lua_tonumber(l, 2);
		return 0;
	}
}