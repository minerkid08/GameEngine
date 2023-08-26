#pragma once
#include "Core/Core.h"
#include "renderer/Camera.h"
#include "renderer/Texture.h"
namespace Engine{
	class API Renderer2D{
		public:
		static void init();
		static void shutdown();

		static void beginScene(const Camera& camera);
		static void endScene();

		static void draw(const glm::vec2 pos, const glm::vec2 size, const glm::vec4 color);
		static void draw(const glm::vec3 pos, const glm::vec2 size, const glm::vec4 color);
		static void draw(const glm::vec2 pos, const glm::vec2 size, const shdPtr<Texture2D>& tex);
		static void draw(const glm::vec3 pos, const glm::vec2 size, const shdPtr<Texture2D>& tex);
		static void draw(const glm::vec2 pos, const glm::vec2 size, const shdPtr<Texture2D>& tex, const glm::vec4 color);
		static void draw(const glm::vec3 pos, const glm::vec2 size, const shdPtr<Texture2D>& tex, const glm::vec4 color);
	};
}