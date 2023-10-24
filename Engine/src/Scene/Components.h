#pragma once
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Core.h"
#include "Core/Log.h"
#include "Core/UUID.h"
#include "Renderer/Camera.h"
#include "Renderer/Texture.h"
namespace Engine{
	class ScriptableObject;
	namespace Components{
		struct Transform{
			glm::vec3 pos;
			glm::vec3 scale = {1.0f, 1.0f, 1.0f};
			glm::vec3 rot = {0.0f, 0.0f, 0.0f};

			Transform() = default;
			Transform(const Transform& t){
				pos = t.pos;
				rot = t.rot;
				scale = t.scale;
			}
			Transform(glm::vec3 _pos, glm::vec3 _scale, glm::vec3 _rot){
				pos = _pos;
				scale = _scale;
				rot = _rot;
			}
			void reset(){
				pos = {0.0f, 0.0f, 0.0f};
				rot = {0.0f, 0.0f, 0.0f};
				scale = {1.0f, 1.0f, 1.0f};
			}
		};
		struct SpriteRenderer{
			enum Type {Color = 0, Tex = 1};
			Type mode = Type::Color;
			glm::vec4 color = {0.0f, 0.0f, 0.0f, 1.0f};
			shdPtr<Texture2D> tex;
			float tile = 1.0f;
			std::string path;
			SpriteRenderer(){
				texture();
			}
			SpriteRenderer(const SpriteRenderer&) = default;
			SpriteRenderer(const glm::vec4 _color){
				color = _color;
			}
			void setMode(int _mode){
				if(_mode == 1){
					mode = Type::Tex;
				}else{
					mode = Type::Color;
				}
			}
			void texture(){
				tex = std::make_shared<Texture2D>(path.empty() ? "Engine/Textures/logo.png" : path.c_str());
			}
			void reset(){
				mode = Type::Color;
				color = {0.0f, 0.0f, 0.0f, 1.0f};
				tile = 1.0f;
				tex = NULL;
			}
		};
		struct Tag{
			std::string tag;
			UUID uuid;
			int order;
			Tag() = default;
			Tag(const Tag&) = default;
			Tag(const std::string& _tag){
				tag = _tag;
			}
		};
		struct Camera{
			Engine::Camera camera;
			bool mainCamera = false;
			bool fixedAspect = false;
			Camera() = default;
			Camera(const Camera&) = default;
			Camera(int width, int height, float zoom = 1){
				camera.orthographic(width, height, zoom);
			}
			void reset(){
				camera.getZoom() = 1;
				camera.orthographic(0, 0);
				mainCamera = false;
				fixedAspect = false;
			}
		};
		struct API NativeScript{
			bool enabled = true;
			bool hasScript = false;
			std::string path;
			shdPtr<ScriptableObject> script = nullptr;
			void (*make)(NativeScript*);
			NativeScript() = default;
			NativeScript(const NativeScript& n){
				enabled = n.enabled;
				hasScript = n.hasScript;
				path = n.path;
				script = n.script;
				make = n.make;
			}
			~NativeScript(){
				destroy();
			}
			template<typename T> void bind(){
				make = [](NativeScript* comp){
					comp->script = std::make_shared<T>();
					comp->script->path = comp->path;
					comp->hasScript = true;
					comp->script->compile();
				};
			}
			void destroy(){
				script = nullptr;
				hasScript = false;
			}
			void reset();
		};
	}
}