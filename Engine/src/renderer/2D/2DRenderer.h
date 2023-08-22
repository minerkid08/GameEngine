#pragma once
#include "Core/Core.h"
#include "renderer/Camera.h"
namespace Engine{
	class API Renderer2D{
		public:
		static void init();
		static void shutdown();

		static void beginScene(const Camera& camera);
		static void endScene();

		static void draw(const glm::vec2 pos, const glm::vec2 size, const glm::vec4 color);
	};
}