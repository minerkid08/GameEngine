#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "VertArray.h"
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
namespace Engine{
	class API Renderer{
		public:
		static void init();

		static void clear();
		static void setClearColor(const glm::vec4& color);

		static void beginScene(Camera& cam);
		static void endScene();
		static void submit(const shdPtr<VertArray>& vertexArray, const shdPtr<Shader>& shader, const glm::mat4x4& transform);
		static void submit(const shdPtr<Mesh>& mesh, int texSlot);

		private:
		struct SceneData{
			glm::mat4x4 viewProjMat;
		};
		static SceneData* sceneData;
	};
}