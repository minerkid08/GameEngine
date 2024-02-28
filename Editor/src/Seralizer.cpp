#include <fstream>
#include "Seralizer.h"
#include "lua/LuaScriptableObject.h"
#include "AssetManager.h"
namespace Engine{
	void Serializer::seralize(const std::string& path){
		json out;
		out["Scene"] = "name";
		out["entities"] = {};
		for(int i = 0; i < scene->entities.size(); i++){
			Entity& ent = scene->entities[i];
			if(!ent){
				continue;;
			}
			seralizeEnt(out, ent);
		};
		std::ofstream fout(path);
		fout << out.dump(4);
	}
	void Serializer::seralizeEnt(json& out, Entity& ent){
		int id = 1;
		json j;
		if(ent.hasComp<Components::Tag>()){
			j["TagComp"] = {
				{"Tag", ent.getComp<Components::Tag>().tag},
				{"UUID", (int)ent.getComp<Components::Tag>().uuid}
			};
		}

		if(ent.hasComp<Components::Transform>()){
			Components::Transform& transform = ent.getComp<Components::Transform>();
			j["TransformComp"] = {
				{"pos", {
					transform.pos.x,
					transform.pos.y,
					transform.pos.z
				}},
				{"rot", transform.rot},
				{"scale", {
					transform.scale.x,
					transform.scale.y
				}}
			};
		}
		if(ent.hasComp<Components::Camera>()){
			Components::Camera& camera = ent.getComp<Components::Camera>();
			j["CameraComp"] = {
				{"Camera", {
					{"near", camera.camera.getNear()},
					{"far", camera.camera.getFar()},
					{"aspect", camera.camera.getAspect()},
					{"zoom", camera.camera.getZoom()}
				}},
				{"fixedAspect", camera.fixedAspect},
				{"mainCamera", camera.mainCamera}
			};
		}
		if(ent.hasComp<Components::SpriteRenderer>()){
			Components::SpriteRenderer& sprite = ent.getComp<Components::SpriteRenderer>();
			j["SpriteRendererComp"] = {
				{"mode", sprite.mode},
				{"color", {
					sprite.color.r,
					sprite.color.g,
					sprite.color.b,
					sprite.color.a
				}},
				{"texUUID", (uint64_t)sprite.texUUID},
				{"tile", sprite.tile},
			};
		}
		if(ent.hasComp<Components::NativeScript>()){
			Components::NativeScript& script = ent.getComp<Components::NativeScript>();
			j["ScriptComp"] = {
				{"active", script.enabled},
				{"hasScript", script.hasScript},
				{"path", script.path}
			};
		}
		out["entities"].push_back(j);
	}
	void Serializer::deseralize(const std::string& path){
		Log::Info(("loading: " + path).c_str());
		std::ifstream stream(path);
		std::stringstream sstream;
		sstream << stream.rdbuf();

		json j = json::parse(sstream);

		json ents = j["entities"];
		int i = 0;
		for(auto ent : ents){
			i++;
			Entity ent2 = scene->createEnt();
			if(ent.contains("TagComp")){
				ent2.getComp<Components::Tag>().tag = ent["TagComp"]["Tag"];
				if(ent["TagComp"].contains("UUID")){
					int uuid = ent["TagComp"]["UUID"];
					ent2.getComp<Components::Tag>().uuid = uuid;
				}
			}
			if(ent.contains("TransformComp")){
				auto& comp = ent2.getComp<Components::Transform>();
				glm::vec3 pos = {
					ent["TransformComp"]["pos"][0],
					ent["TransformComp"]["pos"][1],
					ent["TransformComp"]["pos"][2]
				};
				glm::vec2 scale = {
					ent["TransformComp"]["scale"][0],
					ent["TransformComp"]["scale"][1]
				};
				comp.pos = pos;
				comp.rot = ent["TransformComp"]["rot"];
				comp.scale = scale;
			}
			if(ent.contains("CameraComp")){
				auto& comp = ent2.addComp<Components::Camera>();
				float aspect = ent["CameraComp"]["Camera"]["aspect"];
				float zoom = ent["CameraComp"]["Camera"]["zoom"];
				float near_ = ent["CameraComp"]["Camera"]["near"];
				float far_ = ent["CameraComp"]["Camera"]["far"];
				comp.camera.orthographic(aspect, zoom, near_, far_);
				comp.fixedAspect = ent["CameraComp"]["fixedAspect"];
				comp.mainCamera = ent["CameraComp"]["mainCamera"];
			}
			if(ent.contains("SpriteRendererComp")){
				auto& comp = ent2.addComp<Components::SpriteRenderer>();
				int mode = ent["SpriteRendererComp"]["mode"];
				glm::vec4 color = {
					ent["SpriteRendererComp"]["color"][0],
					ent["SpriteRendererComp"]["color"][1],
					ent["SpriteRendererComp"]["color"][2],
					ent["SpriteRendererComp"]["color"][3]
				};
				UUID id = (int64_t)ent["SpriteRendererComp"]["texUUID"];
				float tile = ent["SpriteRendererComp"]["tile"];

				comp.color = color;
				comp.texUUID = id;
				comp.tile = tile;
				comp.setMode(mode);
				if(mode == Components::SpriteRenderer::Type::Tex){
					comp.setTex(AssetManager::instance->getTex(id)->getTexture());
				}
			}
			if(ent.contains("ScriptComp")){
				auto& comp = ent2.addComp<Components::NativeScript>();
				bool active = ent["ScriptComp"]["active"];
				bool hasScript = ent["ScriptComp"]["hasScript"];
				comp.enabled = active;
				comp.path = ent["ScriptComp"]["path"];
				comp.bind<LuaScriptableObject>();
			}
		}
		Log::Info("done: " + std::to_string(i) + " entities");
	}
}