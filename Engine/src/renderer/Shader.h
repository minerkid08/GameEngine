#pragma once
#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <map>
#include <glm/glm.hpp>
#include "../Core.h"

namespace Engine{
	class API Shader{
		public:
		Shader(const std::string& filename);
		~Shader();
		void run();
		void unbind();

		void loadUniform(const std::string& name);

		void setValue(const std::string& name, int value);
		void setValue(const std::string& name, float value);
		void setValue(const std::string& name, const glm::vec2& value);
		void setValue(const std::string& name, const glm::vec3& value);
		void setValue(const std::string& name, const glm::vec4& value);
		void setValue(const std::string& name, const glm::mat2x2& value);
		void setValue(const std::string& name, const glm::mat3x3& value);
		void setValue(const std::string& name, const glm::mat4x4& value);
		//void setValue(std::string name, bool value);

		private:
		unsigned int prgmid;
		std::map<std::string, int> uniforms;
	};
}