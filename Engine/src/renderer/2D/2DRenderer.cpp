#include "2DRenderer.h"
#include "Core/Core.h"
#include "renderer/VertArray.h"
#include "renderer/Buffer.h"
#include "renderer/Shader.h"
namespace Engine{
	struct QuadVert{
		glm::vec3 pos;
		glm::vec4 color;
		glm::vec2 texCord;
	};
	struct Renderer2dData{
		const int maxQuads = 10000;
		const int maxVerts = maxQuads * 4;
		const int maxInds = maxQuads * 6;

		int indCount;

		shdPtr<VertArray> vertArray;
		shdPtr<VertBuffer> vertBuffer;
		shdPtr<Shader> texShader;
		shdPtr<Texture2D> whiteTex;

		QuadVert* vertBase = nullptr;
		QuadVert* vertPtr = nullptr;
	};
	static Renderer2dData data;
	void Renderer2D::init(){
		data.vertArray = std::make_shared<VertArray>();
		data.vertBuffer = std::make_shared<VertBuffer>(data.maxVerts * sizeof(QuadVert));
		data.vertBuffer->setLayout({
			{ShaderType::Float3, "pos"},
			{ShaderType::Float4, "color"},
			{ShaderType::Float2, "texCord"}
		});
		data.vertArray->addVertBuffer(data.vertBuffer);

		data.vertBase = new QuadVert[data.maxVerts];

		unsigned int* ind = new unsigned int[data.maxInds];
		unsigned offset = 0;
		for(int i = 0; i < data.maxInds; i += 6){
			ind[i+0] = offset + 0;
			ind[i+1] = offset + 1;
			ind[i+2] = offset + 2;
			ind[i+3] = offset + 2;
			ind[i+4] = offset + 3;
			ind[i+5] = offset + 0;
			offset += 4;
		}

		shdPtr<IndBuffer> ib = std::make_shared<IndBuffer>(ind, data.maxInds);
		data.vertArray->setIndBuffer(ib);

		delete[] ind;

		data.texShader = std::make_shared<Shader>("Engine/shaders/shader.glsl");
		data.texShader->loadUniform("viewProj");
		//data.texShader->loadUniform("transform");
		//data.texShader->loadUniform("color");
		//data.texShader->loadUniform("tile");
		//data.texShader->loadUniform("tex");

		data.whiteTex = std::make_shared<Texture2D>(1,1);
		int data2 = 0xffffffff;
		data.whiteTex->setData(&data2,4);
	}
	void Renderer2D::shutdown(){}
	void Renderer2D::beginScene(const Camera& camera){
		data.texShader->run();
		data.texShader->setValue("viewProj", camera.getViewProjMat());
		data.vertPtr = data.vertBase;
		data.indCount = 0;
	}
	void Renderer2D::endScene(){
		unsigned int size = (uint8_t*)data.vertPtr - (uint8_t*)data.vertBase;
		data.vertBuffer->setData(data.vertBase, size);
		glDrawElements(GL_TRIANGLES, data.indCount, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void Renderer2D::draw(const Transform& transform, const glm::vec4 color){
		drawInt(transform.getMat(), color, data.whiteTex, 1);
	}
	void Renderer2D::draw(const Transform& transform, const shdPtr<Texture2D>& tex, float tile){
		drawInt(transform.getMat(), glm::vec4(1.0f), tex, tile);
	}
	void Renderer2D::draw(const Transform& transform, const shdPtr<Texture2D>& tex, const glm::vec4 color, float tile){
		drawInt(transform.getMat(), color, tex, tile);
	}
	void Renderer2D::drawInt(glm::mat4x4 transform, const glm::vec4 color, const shdPtr<Texture2D>& tex, float tile){
		data.vertPtr->pos = transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		data.vertPtr->color = color;
		data.vertPtr->texCord = {0.0f, 0.0f};
		data.vertPtr++;

		data.vertPtr->pos = transform * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		data.vertPtr->color = color;
		data.vertPtr->texCord = {1.0f, 0.0f};
		data.vertPtr++;

		data.vertPtr->pos = transform * glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
		data.vertPtr->color = color;
		data.vertPtr->texCord = {1.0f, 1.0f};
		data.vertPtr++;

		data.vertPtr->pos = transform * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
		data.vertPtr->color = color;
		data.vertPtr->texCord = {0.0f, 1.0f};
		data.vertPtr++;

		data.indCount+=6;

		//data.texShader->setValue("tile", tile);
		//data.texShader->setValue("tex", 0);
		//data.vertArray->bind();
		//tex->bind();
		//glDrawElements(GL_TRIANGLES, data.vertArray->getIndBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}
}