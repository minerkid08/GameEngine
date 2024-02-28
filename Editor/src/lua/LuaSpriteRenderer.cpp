#include "LuaSpriteRenderer.h"
#include "AssetManager.h"
namespace Engine{
	int LuaSpriteRenderer::make(lua_State* l, const Entity& ent){
		lua_newtable(l);
		int spritePos = lua_gettop(l);

		lua_pushcfunction(l, getTint);
		lua_setfield(l, -2, "getTint");

		lua_pushcfunction(l, setTint);
		lua_setfield(l, -2, "setTint");

		lua_pushcfunction(l, getTile);
		lua_setfield(l, -2, "getTile");

		lua_pushcfunction(l, setTile);
		lua_setfield(l, -2, "setTile");
		
		lua_pushcfunction(l, getUv);
		lua_setfield(l, -2, "getUV");

		lua_pushcfunction(l, setUv);
		lua_setfield(l, -2, "setUV");
		
		lua_pushcfunction(l, getTex);
		lua_setfield(l, -2, "getTex");

		lua_pushcfunction(l, setTex);
		lua_setfield(l, -2, "setTex");

		lua_pushcfunction(l, setMode);
		lua_setfield(l, -2, "setMode");

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
	
	int LuaSpriteRenderer::setTile(lua_State* l){
		getComp();
		renderer.tile = lua_tonumber(l, 2);
		return 0;
	}
	
	int LuaSpriteRenderer::getTile(lua_State* l){
		getComp();
		lua_pushnumber(l, renderer.tile);
		return 1;
	}

	int LuaSpriteRenderer::setUv(lua_State* l){
		lua_getfield(l, 3, "x");
		float x = lua_tonumber(l, -1);
		lua_pop(l, 1);
		lua_getfield(l, 3, "y");
		float y = lua_tonumber(l, -1);
		lua_pop(l, 1);
		int ind = lua_tointeger(l, 2);
		getComp();
		renderer.uvs[ind].x = x;
		renderer.uvs[ind].y = y;
		return 0;
	}
	
	int LuaSpriteRenderer::getUv(lua_State* l){
		getComp();
		int ind = lua_tointeger(l, 2);
		float x = renderer.uvs[ind].x;
		float y = renderer.uvs[ind].y;
		lua_newtable(l);
		lua_pushnumber(l, x);
		lua_setfield(l, -1, "x");
		lua_pushnumber(l, y);
		lua_setfield(l, -1, "y");
		return 1;
	}

	int LuaSpriteRenderer::setTex(lua_State* l){
		getComp();
		renderer.texUUID = lua_tointeger(l, 2);
		renderer.setTex(AssetManager::instance->getTex(renderer.texUUID)->getTexture());
		return 0;
	}
	int LuaSpriteRenderer::getTex(lua_State* l){
		getComp();
		lua_pushinteger(l, renderer.texUUID);
		return 1;
	}
	int LuaSpriteRenderer::setMode(lua_State* l){
		std::string name = lua_tostring(l, 2);
		getComp();
		if(name == "sprite"){
			renderer.setMode(Components::SpriteRenderer::Type::Tex);
		}
		if(name == "color"){
			renderer.setMode(Components::SpriteRenderer::Type::Tex);
		}
	}
}
