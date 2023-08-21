#include "Renderer.h"
#include <glad/glad.h>
namespace Engine{
	Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData;
	void Renderer::init(){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	void Renderer::clear(){
		glClear(GL_COLOR_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	}
	void Renderer::setClearColor(const glm::vec4& color){
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void Renderer::beginScene(OrthoCamera& cam){
		sceneData->viewProjMat = cam.getViewProjMat();
	}
	void Renderer::endScene(){

	}
	void Renderer::submit(const shdPtr<VertArray>& vertexArray, const shdPtr<Shader>& shader, const glm::mat4x4& transform = glm::mat4x4(1.0f)){
		shader->run();
		shader->setValue("viewProj", sceneData->viewProjMat);
		shader->setValue("transform", transform);
		vertexArray->bind();
		glDrawElements(GL_TRIANGLES, vertexArray->getIndBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}
	void Renderer::submit(const shdPtr<Mesh>& mesh, int texSlot){
		mesh->getMaterial()->getShader()->run();
		mesh->getMaterial()->getShader()->setValue("viewProj", sceneData->viewProjMat);
		mesh->getMaterial()->getShader()->setValue("transform", mesh->getTransform());
		if(mesh->getMaterial()->getType() == Material::MaterialType::Texture){
			mesh->getMaterial()->getShader()->setValue("tex", texSlot);
			mesh->getMaterial()->getTexture()->bind(texSlot);
		}else{
			mesh->getMaterial()->getShader()->setValue("color", mesh->getMaterial()->getColor());
		}
		mesh->getVertArray()->bind();
		glDrawElements(GL_TRIANGLES, mesh->getVertArray()->getIndBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}
}