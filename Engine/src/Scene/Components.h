#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Core.h"
#include "Renderer/Camera.h"
#include "ScriptableObject.h"
#include "Renderer/Texture.h"
namespace Engine{
	namespace Components{
		struct Transform{
			glm::vec3 pos;
			glm::vec2 scale = {1.0f, 1.0f};
			float rot;

			Transform() = default;
			Transform(const Transform&) = default;
			Transform(glm::vec3 _pos, glm::vec2 _scale, float _rot){
				pos = _pos;
				scale = _scale;
				rot = _rot;
			}
			void reset(){
				pos = {0.0f, 0.0f, 0.0f};
				rot = 0.0f;
				scale = {1.0f, 1.0f};
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
		struct NativeScript{
			bool enabled = true;
			ScriptableObject* script = nullptr;
			std::function<void()> instScript;
			std::function<void()> destScript;
			template<typename T> void bind(){
				instScript = [&](){
					script = new T();
				};
				destScript = [&](){
					delete script;
					script = nullptr;
				};
			}
			void reset(){
				enabled = true;
			}
		};
	}
}