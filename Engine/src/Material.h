#pragma once
#include "renderer/Shader.h"
#include "renderer/Texture.h"
#include "Log.h"
namespace Engine{
	class API Material{
		public:
		enum MaterialType{
			SolidColor,
			Texture
		};
		static shdPtr<Material> MakeSolidColor(glm::vec3 color){
			shdPtr<Material> mat = std::make_shared<Material>();
			mat->setType(MaterialType::SolidColor);
			mat->setColor(color);
			mat->setShader(std::make_shared<Shader>("Engine/shaders/color.glsl"));
			return mat;
		}
		static shdPtr<Material> MakeTexture(const std::string& filename){
			shdPtr<Material> mat = std::make_shared<Material>();
			mat->setType(MaterialType::Texture);
			mat->setShader(std::make_shared<Shader>("Engine/shaders/texture.glsl"));
			mat->setTexture(std::make_shared<Texture2D>(filename));
			return mat;
		}
		void setShader(shdPtr<Shader> _shader){
			shader = _shader;
			shader->loadUniform("viewProj");
			shader->loadUniform("transform");
			if(type == MaterialType::SolidColor){
				shader->loadUniform("color");
			}
			if(type == MaterialType::Texture){
				shader->loadUniform("tex");
			}
		}
		void setTexture(shdPtr<Texture2D> tex){texture = tex;}
		void setColor(glm::vec3 _color){color = _color;}
		void setType(MaterialType _type){type = _type;}
		shdPtr<Shader> getShader(){return shader;}
		shdPtr<Texture2D> getTexture(){return texture;}
		glm::vec3 getColor(){return color;}
		MaterialType getType(){return type;}
		void draw();
		private:
		MaterialType type;
		glm::vec3 color;
		shdPtr<Shader> shader;
		shdPtr<Texture2D> texture;
	};
}