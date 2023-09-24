#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Core.h"
#include "Renderer/Camera.h"
#include "ScriptableObject.h"
namespace Engine{
	namespace Components{
		struct Transform{
			glm::vec3 pos;
			glm::vec2 scale;
			float rot;

			Transform() = default;
			Transform(const Transform&) = default;
			Transform(glm::vec3 _pos, glm::vec2 _scale, float _rot){
				pos = _pos;
				scale = _scale;
				rot = _rot;
			}
		};
		struct SpriteRenderer{
			glm::vec4 color;
			SpriteRenderer() = default;
			SpriteRenderer(const SpriteRenderer&) = default;
			SpriteRenderer(const glm::vec4 _color){
				color = _color;
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
			Camera(float aspect, float zoom){
				camera.orthographic(-aspect * zoom, aspect * zoom, zoom, -zoom);
			}
		};
		struct NativeScript{
			ScriptableObject* script = nullptr;
			std::function<void()> instFn;
			std::function<void()> destInstFn;
			std::function<void()> createFn;
			std::function<void()> destroyFn;
			std::function<void(float)> updateFn;
			template<typename T> void bind(){
				instFn = [&](){script = new T();};
				destInstFn = [&](){delete script;};

				createFn = [&](){((T*)script)->create();};
				destroyFn = [&](){((T*)script)->destroy();};
				updateFn = [&](float deltaTime){((T*)script)->update(deltaTime);};
			}
		};
	}
}