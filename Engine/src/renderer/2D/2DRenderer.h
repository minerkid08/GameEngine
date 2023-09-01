#pragma once
#include "Core/Core.h"
#include "Core/Transform.h"
#include "renderer/Camera.h"
#include "renderer/Texture.h"
namespace Engine{
	struct RendererData{
		Transform transform;
		shdPtr<Texture2D> tex;
		float tile = 1.0f;
		glm::vec4 color = glm::vec4(1.0f);
	};
	class API Renderer2D{
		public:
		static void init();
		static void shutdown();

		static void beginScene(const Camera& camera);
		static void endScene();

		static void draw(const Transform& transform, const glm::vec4 color);
		static void draw(const Transform& transform, const shdPtr<Texture2D>& tex, float tile = 1);
		static void draw(const Transform& transform, const shdPtr<Texture2D>& tex, const glm::vec4 color, float tile = 1);
		static void draw(const RendererData& data);
		static void drawInt(glm::mat4x4 transform, const glm::vec4 color, const shdPtr<Texture2D>& tex, float tile);
	};
}