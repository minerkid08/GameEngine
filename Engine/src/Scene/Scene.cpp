#include "Scene.h"
#include "Entity.h"
#include "Components.h"
#include "Renderer/2D/2DRenderer.h"
#include <glm/glm.hpp>
namespace Engine{
	Scene::Scene(){
		
	}
	Scene::~Scene(){

	}
	void Scene::update(float deltaTime){
		auto scriptGroup = registry.view<Components::NativeScript>();
		for(auto& ent : scriptGroup){
			auto& comp = scriptGroup.get<Components::NativeScript>(ent);
			if(!comp.script){
				comp.instFn();
				comp.script->ent = {this, ent};
				comp.createFn();
			}
			comp.updateFn(deltaTime);
		}

		bool drawing = false;
		auto cameraGroup = registry.group<Components::Camera>(entt::get<Components::Transform>);
		for(auto& ent : cameraGroup){
			auto [camera, transform] = cameraGroup.get<Components::Camera, Components::Transform>(ent);
			if(camera.mainCamera){
				camera.camera.setPos(transform.pos);
				camera.camera.setRot(transform.rot);
				Renderer2D::beginScene(camera.camera);
				drawing = true;
				
			}
		}
		if(!drawing){return;}
		auto group = registry.group<Components::Transform>(entt::get<Components::SpriteRenderer>);
		for(auto ent : group){
			auto [transform, sprite] = group.get<Components::Transform, Components::SpriteRenderer>(ent);
			Renderer2D::draw({transform.pos, transform.rot, transform.scale}, sprite.color);
		}
		Renderer2D::endScene();
	}
	Entity Scene::createEnt(const std::string& name){
		Entity ent = {this, registry.create()};
		ent.addComp<Components::Transform>();
		ent.addComp<Components::Tag>(name);
		return ent;
	}
	void Scene::viewportResize(int _width, int _height, float zoom){
		width = _width;
		height = _height;
		auto view = registry.view<Components::Camera>();
		for(auto ent : view){
			auto& camera = view.get<Components::Camera>(ent);
			if(!camera.fixedAspect){
				float aspect = (float)width / (float)height;
				camera.camera.orthographic(-aspect * zoom, aspect * zoom, zoom, -zoom);
			}
		}
	}
}