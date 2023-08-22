#include "2DRenderer.h"
#include "Core/Core.h"
#include "renderer/VertArray.h"
#include "renderer/Buffer.h"
#include "renderer/Shader.h"
namespace Engine{
	struct Renderer2dData{
		shdPtr<VertArray> vertArray;
		shdPtr<Shader> colorShader;
	};
	static Renderer2dData* data;
	void Renderer2D::init(){
		data = new Renderer2dData();
		data->vertArray = std::make_shared<VertArray>();
		float verts[4*4] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};
		shdPtr<VertBuffer> vb = std::make_shared<VertBuffer>(verts, sizeof(verts));
		vb->setLayout({
			{ShaderType::Float3, "pos"}
		});
		data->vertArray->addVertBuffer(vb);
		unsigned int ind[6] = {0,1,2,2,3,0};
		shdPtr<IndBuffer> va = std::make_shared<IndBuffer>(ind, 6);
		data->vertArray->setIndBuffer(va);
		data->colorShader = std::make_shared<Shader>("Engine/shaders/color.glsl");
		data->colorShader->loadUniform("viewProj");
		data->colorShader->loadUniform("transform");
		data->colorShader->loadUniform("color");
	}
	void Renderer2D::shutdown(){
		delete data;
	}
	void Renderer2D::beginScene(const Camera& camera){
		data->colorShader->run();
		data->colorShader->setValue("viewProj", camera.getViewProjMat());
	}
	void Renderer2D::endScene(){

	}
	void Renderer2D::draw(const glm::vec2 pos, const glm::vec2 size, const glm::vec4 color){
		data->colorShader->run();
		data->colorShader->setValue("transform", glm::translate(glm::mat4x4(1.0f), glm::vec3(pos, 0.0f)) * glm::scale(glm::mat4x4(1.0f), glm::vec3(size, 1.0f)));
		data->colorShader->setValue("color", color);
		data->vertArray->bind();
		glDrawElements(GL_TRIANGLES, data->vertArray->getIndBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}
}