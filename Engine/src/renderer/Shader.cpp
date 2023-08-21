#include "Shader.h"
#include <string>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include "../Log.h"
namespace Engine{
	static int typeFromString(const std::string& type){
		if(type == "frag"){return GL_FRAGMENT_SHADER;}
		if(type == "vert"){return GL_VERTEX_SHADER;}
		return 0;
	}
	static std::string stringFromType(int type){
		if(type == GL_FRAGMENT_SHADER){return "frag";}
		if(type == GL_VERTEX_SHADER){return "vert";}
		return "Invalid type";
	}
	Shader::Shader(const std::string& filename){
		std::string data;
		std::ifstream file(filename, std::ios::binary);
		if(file){
			file.seekg(0, std::ios::end);
			data.resize(file.tellg());
			file.seekg(0, std::ios::beg);
			file.read(&data[0], data.size());
			file.close();
		}else{
			Log::Error("Cannot open file: " + filename);
		}

		std::unordered_map<int, std::string> map;

		const char* typeToken = "$";
		int len = strlen(typeToken);
		int pos = data.find(typeToken, 0);
		while(pos != std::string::npos){
			int eol = data.find_first_of("\r\n", pos);
			if(eol == std::string::npos){
				Log::Error("Syntax error");
			}
			int begin = pos + len;
			std::string type = data.substr(begin, eol - begin);
			if(!(type == "vert" || type == "frag")){
				Log::Error("Invalid shader type: " + type);
			}
			int nextPos = data.find_first_of("\r\n", eol);
			pos = data.find(typeToken, nextPos);
			map[typeFromString(type)] = data.substr(nextPos, pos - (nextPos == std::string::npos ? data.size() - 1 : nextPos));
		}
		std::vector<unsigned int> ids;
		for(auto& kv : map){
			int type = kv.first;
			std::string srcs = kv.second;
			GLuint id = glCreateShader(type);
			const GLchar* src = srcs.c_str();
			glShaderSource(id, 1, &src, 0);
			glCompileShader(id);
			int compiled = 0;
			glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
			if(compiled == GL_FALSE){
				GLint len = 0;
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
				char infoLog[len];
				glGetShaderInfoLog(id, len, &len, infoLog);
				glDeleteShader(id);
				std::string str(infoLog);
				Log::Error(stringFromType(type) + " shader compilation failed: " + str);
				return;
			}
			ids.push_back(id);
		}
		prgmid = glCreateProgram();
		for(auto& id : ids){
			glAttachShader(prgmid, id);
		}
		glLinkProgram(prgmid);

		int linked = 0;
		glGetProgramiv(prgmid, GL_LINK_STATUS, &linked);
		if(linked == GL_FALSE){
			int len = 0;
			glGetProgramiv(prgmid, GL_INFO_LOG_LENGTH, &len);
			char infoLog[len];
			glGetProgramInfoLog(prgmid, len, &len, infoLog);
			glDeleteProgram(prgmid);
			for(auto& id : ids){
				glDeleteShader(id);
			}
			std::string str(infoLog);
			Log::Error("Shader linking failed: " + str);
			return;
		}
		for(auto& id : ids){
			glDeleteShader(id);
		}
	}
	Shader::~Shader(){
		glDeleteProgram(prgmid);
	}
	void Shader::loadUniform(const std::string& name){
		int id = glGetUniformLocation(prgmid, name.c_str());
		if(id == -1){
			Log::Error("Uniform " + name + " not found");
			return;
		}
		uniforms[name] = id;
	}
	void Shader::run(){
		glUseProgram(prgmid);
	}
	void Shader::unbind(){
		glUseProgram(0);
	}
	void Shader::setValue(const std::string& name, int value){
		glUniform1i(uniforms[name], value);
	}
	void Shader::setValue(const std::string& name, float value){
		glUniform1f(uniforms[name], value);
	}
	void Shader::setValue(const std::string& name, const glm::vec2& value){
		glUniform2f(uniforms[name], value.x, value.y);
	}
	void Shader::setValue(const std::string& name, const glm::vec3& value){
		glUniform3f(uniforms[name], value.x, value.y, value.z);
	}
	void Shader::setValue(const std::string& name, const glm::vec4& value){
		glUniform4f(uniforms[name], value.x, value.y, value.z, value.w);
	}
	void Shader::setValue(const std::string& name, const glm::mat2x2& value){
		glUniformMatrix2fv(uniforms[name], 1, GL_FALSE, glm::value_ptr(value));
	}
	void Shader::setValue(const std::string& name, const glm::mat3x3& value){
		glUniformMatrix3fv(uniforms[name], 1, GL_FALSE, glm::value_ptr(value));
	}
	void Shader::setValue(const std::string& name, const glm::mat4x4& value){
		glUniformMatrix4fv(uniforms[name], 1, GL_FALSE, glm::value_ptr(value));
	}
}