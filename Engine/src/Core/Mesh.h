#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Core.h"
#include "Material.h"
#include "renderer/VertArray.h"
namespace Engine{
	class API Mesh{
		public:
		static shdPtr<Mesh> Plane(const shdPtr<Material>& mat){
			shdPtr<VertArray> va = std::make_shared<VertArray>();
			float verts[4*5] = {
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
				 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
				 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
				-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
			};
			shdPtr<VertBuffer> vb = std::make_shared<VertBuffer>(verts, sizeof(verts));
			vb->setLayout({
				{ShaderType::Float3, "pos"},
				{ShaderType::Float2, "texCord"}
			});
			va->addVertBuffer(vb);

			unsigned int indices[6] = {0, 1, 2, 0, 2, 3};
			shdPtr<IndBuffer> ib = std::make_shared<IndBuffer>(indices, 6);
			va->setIndBuffer(ib);

			return std::make_shared<Mesh>(va,mat);
		}

		Mesh(const shdPtr<VertArray>& va, const shdPtr<Material>& mat){
			vertArray = va;
			material = mat;
			recalcTransform();
		}

		shdPtr<Material> getMaterial(){return material;}
		shdPtr<VertArray> getVertArray(){return vertArray;}
		glm::mat4x4 getTransform(){return transform;}
		
		void setPos(glm::vec3 _pos){
			pos = _pos;
			recalcTransform();
		}
		void setRot(float _rot){
			rot = _rot;
			recalcTransform();
		}
		void setScale(glm::vec3 _scale){
			scale = _scale;
			recalcTransform();
		}

		private:
		shdPtr<VertArray> vertArray;
		shdPtr<Material> material;

		glm::mat4x4 transform;
		glm::vec3 pos = {0,0,0};
		float rot = 0.0f;
		glm::vec3 scale = {1,1,1};

		void recalcTransform(){
			transform = glm::scale(glm::mat4x4(1.0f), scale);
			transform = glm::translate(transform, pos);
			transform = glm::rotate(transform, rot, glm::vec3(0.0f, 0.0f, 1.0f));
		}
	};
}