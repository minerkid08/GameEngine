#include "2DRenderer.h"
#include "Core/Core.h"
#include "renderer/VertArray.h"
#include "renderer/Buffer.h"
#include "renderer/Shader.h"
namespace Engine{
	struct Renderer2dData{
		shdPtr<VertArray> vertArray;
		shdPtr<Shader> texShader;
		shdPtr<Texture2D> whiteTex;
	};
	static Renderer2dData* data;
	void Renderer2D::init(){
		data = new Renderer2dData();
		data->vertArray = std::make_shared<VertArray>();
		float verts[4*6] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
		};
		shdPtr<VertBuffer> vb = std::make_shared<VertBuffer>(verts, sizeof(verts));
		vb->setLayout({
			{ShaderType::Float3, "pos"},
			{ShaderType::Float2, "texCord"}
		});
		data->vertArray->addVertBuffer(vb);
		unsigned int ind[6] = {0,1,2,2,3,0};
		shdPtr<IndBuffer> va = std::make_shared<IndBuffer>(ind, 6);
		data->vertArray->setIndBuffer(va);

		data->texShader = std::make_shared<Shader>("Engine/shaders/shader.glsl");
		data->texShader->loadUniform("viewProj");
		data->texShader->loadUniform("transform");
		data->texShader->loadUniform("color");
		data->texShader->loadUniform("tex");

		data->whiteTex = std::make_shared<Texture2D>(1,1);
		int data2 = 0xffffffff;
		data->whiteTex->setData(&data2,4);
	}
	void Renderer2D::shutdown(){
		delete data;
	}
	void Renderer2D::beginScene(const Camera& camera){
		data->texShader->run();
		data->texShader->setValue("viewProj", camera.getViewProjMat());
	}
	void Renderer2D::endScene(){

	}
	void Renderer2D::draw(const glm::vec2 pos, const glm::vec2 size, const glm::vec4 color){
		data->texShader->setValue("transform", glm::translate(glm::mat4x4(1.0f), glm::vec3(pos, 0.0f)) * glm::scale(glm::mat4x4(1.0f), glm::vec3(size, 1.0f)));
		data->texShader->setValue("color", color);
		data->vertArray->bind();
		data->whiteTex->bind();
		glDrawElements(GL_TRIANGLES, data->vertArray->getIndBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}
	void Renderer2D::draw(const glm::vec3 pos, const glm::vec2 size, const glm::vec4 color){
		data->texShader->setValue("transform", glm::translate(glm::mat4x4(1.0f), pos) * glm::scale(glm::mat4x4(1.0f), glm::vec3(size, 1.0f)));
		data->texShader->setValue("color", color);
		data->vertArray->bind();
		data->whiteTex->bind();
		glDrawElements(GL_TRIANGLES, data->vertArray->getIndBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}
	void Renderer2D::draw(const glm::vec2 pos, const glm::vec2 size, const shdPtr<Texture2D>& tex){
		data->texShader->setValue("color", glm::vec4(1.0f));
		data->texShader->setValue("transform", glm::translate(glm::mat4x4(1.0f), glm::vec3(pos, 0.0f)) * glm::scale(glm::mat4x4(1.0f), glm::vec3(size, 1.0f)));
		data->texShader->setValue("tex", 0);
		data->vertArray->bind();
		tex->bind();
		glDrawElements(GL_TRIANGLES, data->vertArray->getIndBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}
	void Renderer2D::draw(const glm::vec3 pos, const glm::vec2 size, const shdPtr<Texture2D>& tex){
		data->texShader->setValue("color", glm::vec4(1.0f));
		data->texShader->setValue("transform", glm::translate(glm::mat4x4(1.0f), pos) * glm::scale(glm::mat4x4(1.0f), glm::vec3(size, 1.0f)));
		data->texShader->setValue("tex", 0);
		data->vertArray->bind();
		tex->bind();
		glDrawElements(GL_TRIANGLES, data->vertArray->getIndBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}
	void Renderer2D::draw(const glm::vec2 pos, const glm::vec2 size, const shdPtr<Texture2D>& tex, const glm::vec4 color){
		data->texShader->setValue("color", color);
		data->texShader->setValue("transform", glm::translate(glm::mat4x4(1.0f), glm::vec3(pos, 0.0f)) * glm::scale(glm::mat4x4(1.0f), glm::vec3(size, 1.0f)));
		data->texShader->setValue("tex", 0);
		data->vertArray->bind();
		tex->bind();
		glDrawElements(GL_TRIANGLES, data->vertArray->getIndBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}
	void Renderer2D::draw(const glm::vec3 pos, const glm::vec2 size, const shdPtr<Texture2D>& tex, const glm::vec4 color){
		data->texShader->setValue("color", color);
		data->texShader->setValue("transform", glm::translate(glm::mat4x4(1.0f), pos) * glm::scale(glm::mat4x4(1.0f), glm::vec3(size, 1.0f)));
		data->texShader->setValue("tex", 0);
		data->vertArray->bind();
		tex->bind();
		glDrawElements(GL_TRIANGLES, data->vertArray->getIndBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}
}