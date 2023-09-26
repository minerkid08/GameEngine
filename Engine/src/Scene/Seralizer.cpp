#include "Seralizer.h"
#include "Entity.h"
#include "Components.h"
#include <fstream>
namespace Engine{
	void Serializer::seralize(const std::string& path){
		json out;
		out["Scene"] = "name";
		out["entities"] = {};
		scene->getReg().each([&](entt::entity id){
			Entity ent = {scene.get(), id};
			if(!ent){
				return;
			}
			seralizeEnt(out, ent);
		});
		std::ofstream fout(path);
		fout << out.dump(4);
	}
	void Serializer::seralizeEnt(json& out, Entity& ent){
		int id = 1;
		json j;
		if(ent.hasComp<Components::Tag>()){
			j["TagComp"] = {
				{"Tag", ent.getComp<Components::Tag>().tag}
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
			j["SpriteComp"] = {
				{"mode", sprite.mode},
				{"color", {
					sprite.color.r,
					sprite.color.g,
					sprite.color.b,
					sprite.color.a
				}},
				{"texPath", sprite.path},
				{"tile", sprite.tile},
			};
		}
		out["entities"].push_back(j);
	}
	void Serializer::deseralize(const std::string& path){
		Log::Info("loading: " + path);
		std::ifstream stream(path);
		std::stringstream sstream;
		sstream << stream.rdbuf();

		json j = json::parse(sstream);

		json ents = j["entities"];
		for(auto ent : ents){
			Entity ent2 = scene->createEnt();
			if(ent.contains("TagComp")){
				ent2.getComp<Components::Tag>().tag = ent["TagComp"]["Tag"];
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
			if(ent.contains("SpriteComp")){
				auto& comp = ent2.addComp<Components::SpriteRenderer>();
				int mode = ent["SpriteComp"]["mode"];
				glm::vec4 color = {
					ent["SpriteComp"]["color"][0],
					ent["SpriteComp"]["color"][1],
					ent["SpriteComp"]["color"][2],
					ent["SpriteComp"]["color"][3]
				};
				std::string path = ent["SpriteComp"]["texPath"];
				float tile = ent["SpriteComp"]["tile"];

				comp.color = color;
				comp.path = path;
				comp.tile = tile;
				comp.setMode(mode);
				comp.texture();
			}
		}
		Log::Info("done");
	}
}