#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
namespace Engine{
	class Transform{
		public:
		glm::vec3 pos = {0.0f, 0.0f, 0.0f};
		float rot = 0;
		glm::vec2 scale = {1.0f, 1.0f};
		glm::mat4x4 getMat() const {
			if(rot == 0){
				return glm::scale(glm::translate(glm::mat4x4(1.0f), pos), glm::vec3(scale, 1.0f));
			}else{
				return glm::scale(
					glm::rotate(
						glm::translate(glm::mat4x4(1.0f), pos), rot, glm::vec3(0.0f,0.0f,1.0f)
					),
					glm::vec3(scale, 1.0f)
				);
			}
		}
	};
}