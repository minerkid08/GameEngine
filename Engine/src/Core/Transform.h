#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
namespace Engine{
	class Transform{
		public:
		glm::vec3 pos = {0.0f, 0.0f, 0.0f};
		glm::vec3 rot = {0.0f, 0.0f, 0.0f};
		glm::vec3 scale = {1.0f, 1.0f, 1.0f};
		glm::mat4x4 getMat() const {
			glm::translate(glm::mat4(1.0f), pos) * glm::toMat4(glm::quat(rot)) * glm::scale(glm::mat4(1.0f), scale);
		}
	};
}