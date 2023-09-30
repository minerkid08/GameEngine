#include "Scene.h"
#include "Entity.h"
#include "Components.h"
#include "ScriptableObject.h"
#include "Renderer/2D/2DRenderer.h"
#include <glm/glm.hpp>
namespace Engine{
	Scene::Scene(){
		
	}
	Scene::~Scene(){

	}
	void Scene::addComp(Entity& ent){
		if(ent.hasComp<Components::Camera>()){
			auto& camera = ent.getComp<Components::Camera>();
			if(!camera.fixedAspect){
				float aspect = (float)width / (float)height;
				camera.camera.orthographic(aspect, camera.camera.getZoom());
			}
		}
	}
	void Scene::updateRuntime(float deltaTime){
		auto scriptGroup = registry.view<Components::NativeScript>();
		for(auto& ent : scriptGroup){
			auto& comp = scriptGroup.get<Components::NativeScript>(ent);
			if(comp.enabled){
				if(!comp.hasScript){
					comp.make(&comp);
					comp.script->ent = {this, ent};
					comp.script->create();
				}
				comp.script->update(deltaTime);
			}
		}

		bool drawing = false;
		auto cameraGroup = registry.group<Components::Camera>(entt::get<Components::Transform>);
		for(auto ent : cameraGroup){
			auto [camera, transform] = cameraGroup.get<Components::Camera, Components::Transform>(ent);
			if(camera.mainCamera){
				camera.camera.setPos(transform.pos);
				camera.camera.setRot(transform.rot);
				Renderer2D::beginScene(camera.camera);
				drawing = true;
			}
		};
		if(!drawing){return;}
		auto group = registry.group<Components::SpriteRenderer>(entt::get<Components::Transform>);
		for(auto ent : group){
			if(Entity(this, ent)){
				auto [transform, sprite] = group.get<Components::Transform, Components::SpriteRenderer>(ent);
				if(sprite.mode == Components::SpriteRenderer::Type::Color){
					Renderer2D::draw({transform.pos, transform.rot, transform.scale}, sprite.color);
				}else{
					Renderer2D::draw({transform.pos, transform.rot, transform.scale}, sprite.tex, sprite.color, sprite.tile);
				}
			}
		}
		Renderer2D::endScene();
	}
	void Scene::updateEditor(float deltaTime, Camera& camera){
		Renderer2D::beginScene(camera);
		auto group = registry.group<Components::Transform>(entt::get<Components::SpriteRenderer>);
		for(auto ent : group){
			auto [transform, sprite] = group.get<Components::Transform, Components::SpriteRenderer>(ent);
			if(sprite.mode == Components::SpriteRenderer::Type::Color){
				Renderer2D::draw({transform.pos, transform.rot, transform.scale}, sprite.color);
			}else{
				Renderer2D::draw({transform.pos, transform.rot, transform.scale}, sprite.tex, sprite.color, sprite.tile);
			}
		}
		Renderer2D::endScene();
	}
	Entity Scene::createEnt(const std::string& name){
		Entity ent = {this, registry.create()};
		ent.addComp<Components::Transform>();
		ent.addComp<Components::Tag>(name);
		return ent;
	}
	void Scene::removeEnt(const Entity& ent){
		registry.destroy(ent);
	}
	void Scene::viewportResize(int _width, int _height){
		width = _width;
		height = _height;
		auto view = registry.view<Components::Camera>();
		for(auto ent : view){
			auto& camera = view.get<Components::Camera>(ent);
			if(!camera.fixedAspect){
				float aspect = (float)width / (float)height;
				camera.camera.orthographic(aspect, camera.camera.getZoom());
			}
		}
	}
	void Scene::stop(){
		auto scriptGroup = registry.view<Components::NativeScript>();
		for(auto& ent : scriptGroup){
			auto& comp = scriptGroup.get<Components::NativeScript>(ent);
			if(comp.enabled && !comp.path.empty()){
				comp.script->destroy();
				comp.destroy();
			}
		}
	}
	template<typename T> static void copyComp(entt::registry& src, entt::registry& dest, const std::unordered_map<UUID, entt::entity>& map){
		auto view = src.view<T>();
		for(auto e : view){
			UUID uuid = src.get<Components::Tag>(e).uuid;
			T& comp = src.get<T>(e);
			dest.emplace_or_replace<T>(map.at(uuid), comp);
		}
	}
	shdPtr<Scene> Scene::copy(){
		shdPtr<Scene> s = std::make_shared<Scene>();
		s->viewportResize(width, height);

		std::unordered_map<UUID, entt::entity> map;

		auto group = registry.view<Components::Transform>();
		for(auto ent : group){
			UUID uuid = registry.get<Components::Tag>(ent).uuid;
			const std::string& name = registry.get<Components::Tag>(ent).tag;
			Entity newEnt = s->createEnt(name);
			newEnt.getComp<Components::Tag>().uuid = uuid;
			map[uuid] = newEnt;
		}
		copyComp<Components::Transform>(registry, s->registry, map);
		copyComp<Components::SpriteRenderer>(registry, s->registry, map);
		copyComp<Components::Camera>(registry, s->registry, map);
		copyComp<Components::NativeScript>(registry, s->registry, map);
		return s;
	}
}