#include "LuaEntity.h"
#include "LuaTransform.h"
#include "LuaTag.h"
namespace Engine{
	void LuaEntity::make(lua_State* l, Entity* ent){
		lua_newtable(l);

		lua_pushlightuserdata(l, ent);
		lua_setfield(l, -2, "id");

		lua_pushcfunction(l, createEnt);
		lua_setfield(l, -2, "add");
		
		lua_pushcfunction(l, getByEntName);
		lua_setfield(l, -2, "getWithName");

		lua_setglobal(l, "Entity");
	}

	int LuaEntity::makeEnt(lua_State* l, const Entity& ent){
		lua_newtable(l);
		int tablePos = lua_gettop(l);

		lua_pushlightuserdata(l, (void*)(entt::entity)ent);
		lua_setfield(l, -2, "id");

		lua_pushcfunction(l, addComp);
		lua_setfield(l, -2, "addComp");

		lua_pushcfunction(l, getComp);
		lua_setfield(l, -2, "getComp");

		lua_pushcfunction(l, hasComp);
		lua_setfield(l, -2, "hasComp");

		lua_pushcfunction(l, removeComp);
		lua_setfield(l, -2, "removeComp");

		return tablePos;
	}

	int LuaEntity::createEnt(lua_State* l){
		const char* name;
		bool hasName = false;
		if(lua_isstring(l, 2)){
			hasName = true;
			name = lua_tostring(l, 2);
		}

		lua_getfield(l, 1, "id");
		Entity* ent = (Entity*)lua_touserdata(l, -1);
		Entity e;
		if(hasName){
			e = ent->getScene()->createEnt(name);
		}else{
			e = ent->getScene()->createEnt();
		}
		makeEnt(l, e);
		return 1;
	}
	int LuaEntity::getByEntName(lua_State* l){
		const char* name;
		bool hasName = false;
		if(lua_isstring(l, 2)){
			hasName = true;
			name = lua_tostring(l, 2);
		}

		lua_getfield(l, 1, "id");
		Entity* ent = (Entity*)lua_touserdata(l, -1);
		Entity e = ent->getScene()->getEntityByName(name);
		makeEnt(l, e);
		return 1;
	}
	static Entity getEnt(lua_State* l){
		lua_getfield(l, 1, "id");
		int ent = (uint64_t)lua_touserdata(l, -1);

		lua_getglobal(l, "Entity");
		lua_getfield(l, -1, "id");
		Entity* scene = (Entity*)lua_touserdata(l, -1);

		Entity e = {scene->getScene(), (entt::entity)ent};
		return e;
	}
	int LuaEntity::getComp(lua_State* l){
		Entity e = getEnt(l);

		const char* name = lua_tostring(l, 2);

		if(strcmp(name, "transform") == 0){
			LuaTransform::make(l, e);
			return 1;
		}
		if(strcmp(name, "tag") == 0){
			LuaTag::make(l, e);
			return 1;
		}
		return 0;
	}
	int LuaEntity::addComp(lua_State* l){
		Entity e = getEnt(l);

		const char* name = lua_tostring(l, 2);

		if(strcmp(name, "transform") == 0){
			e.addComp<Components::Transform>();
			LuaTransform::make(l, e);
			return 1;
		}
		return 0;
	}
	int LuaEntity::hasComp(lua_State* l){
		Entity e = getEnt(l);

		const char* name = lua_tostring(l, 2);

		if(strcmp(name, "transform") == 0){
			lua_pushboolean(l, e.hasComp<Components::Transform>());
			return 1;
		}
		if(strcmp(name, "tag") == 0){
			lua_pushboolean(l, true);
			return 1;
		}
		return 0;
	}
	int LuaEntity::removeComp(lua_State* l){
		Entity e = getEnt(l);

		const char* name = lua_tostring(l, 2);

		if(strcmp(name, "transform") == 0){
			e.removeComp<Components::Transform>();
			return 0;
		}
		return 0;
	}
}