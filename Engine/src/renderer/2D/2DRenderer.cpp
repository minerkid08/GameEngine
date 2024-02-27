#include "2DRenderer.h"
#include "Core/Core.h"
#include "renderer/VertArray.h"
#include "renderer/Buffer.h"
#include "renderer/Shader.h"
#include <array>
namespace Engine{
	struct QuadVert{
		glm::vec3 pos;
		glm::vec4 color;
		glm::vec2 texCord;
		float texIndex;
		glm::vec2 tile;
	};
	struct Renderer2dData{
		const int maxQuads = 10000;
		const int maxVerts = maxQuads * 4;
		const int maxInds = maxQuads * 6;
		static const int maxTexSlots = 32;

		int indCount;

		shdPtr<VertArray> vertArray;
		shdPtr<VertBuffer> vertBuffer;
		shdPtr<Shader> texShader;
		shdPtr<Texture2D> whiteTex;

		QuadVert* vertBase = nullptr;
		QuadVert* vertPtr = nullptr;

		std::array<shdPtr<Texture2D>, maxTexSlots> texSlots;
		unsigned int texSlotInd = 1;
	};
	static Renderer2dData data;
	void Renderer2D::init(){
		data.vertArray = std::make_shared<VertArray>();
		data.vertBuffer = std::make_shared<VertBuffer>(data.maxVerts * sizeof(QuadVert));
		data.vertBuffer->setLayout({
			{ShaderType::Float3, "pos"},
			{ShaderType::Float4, "color"},
			{ShaderType::Float2, "texCord"},
			{ShaderType::Float, "tex"},
			{ShaderType::Float2, "texTile"}
		});
		data.vertArray->addVertBuffer(data.vertBuffer);

		data.vertBase = new QuadVert[data.maxVerts];
		data.vertPtr = data.vertBase;

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
		data.texShader->loadUniform("tex");

		int texs[data.maxTexSlots];
		for(int i = 0; i < data.maxTexSlots; i++){
			texs[i] = i;
		}
		data.texShader->run();
		data.texShader->setValue("tex", texs, data.maxTexSlots);

		data.whiteTex = std::make_shared<Texture2D>(1,1);
		int data2 = 0xffffffff;
		data.whiteTex->setData(&data2,4);
		data.texSlots[0] = data.whiteTex;
	}
	void Renderer2D::shutdown(){}
	void Renderer2D::beginScene(const Camera& camera){
		data.texShader->run();
		data.texShader->setValue("viewProj", camera.getViewProjMat());
		data.texSlotInd = 1;
	}
	void Renderer2D::endScene(){
		drawToScreen();
	}
	void Renderer2D::drawToScreen(){

		unsigned int size = (uint8_t*)data.vertPtr - (uint8_t*)data.vertBase;
		data.vertBuffer->setData(data.vertBase, size);
		for(int i = 0; i < data.texSlotInd; i++){
			data.texSlots[i]->bind(i);
		}
		glDrawElements(GL_TRIANGLES, data.indCount, GL_UNSIGNED_INT, nullptr);
		data.vertPtr = data.vertBase;
		data.indCount = 0;
	}
	void Renderer2D::draw(const Transform& transform, const glm::vec4 color){
		drawInt(transform.getMat(), color, data.whiteTex, {1,1});
	}
	void Renderer2D::draw(const Transform& transform, const shdPtr<Texture2D>& tex, float tile){
		drawInt(transform.getMat(), glm::vec4(1.0f), tex, {tile, tile});
	}
	void Renderer2D::draw(const Transform& transform, const shdPtr<Texture2D>& tex, const glm::vec4 color, float tile){
		drawInt(transform.getMat(), color, tex, {tile,tile});
	}
	void Renderer2D::draw(const Transform& transform, const shdPtr<Texture2D>& tex, const glm::vec4 color, glm::vec2 tile){
		drawInt(transform.getMat(), color, tex, tile);
	}

	void Renderer2D::draw(const Transform& transform, const shdPtr<Texture2D>& tex, float tile, glm::vec2* uvs){
		drawInt(transform.getMat(), glm::vec4(1.0f), tex, {tile, tile}, uvs);
	}
	void Renderer2D::draw(const Transform& transform, const shdPtr<Texture2D>& tex, const glm::vec4 color, float tile, glm::vec2* uvs){
		drawInt(transform.getMat(), color, tex, {tile,tile}, uvs);
	}
	void Renderer2D::draw(const Transform& transform, const shdPtr<Texture2D>& tex, const glm::vec4 color, glm::vec2 tile, glm::vec2* uvs){
		drawInt(transform.getMat(), color, tex, tile, uvs);
	}

	void Renderer2D::draw(const Transform& transform, const shdPtr<SubTex2D>& tex, float tile){
		drawInt(transform.getMat(), glm::vec4(1.0f), tex->getTex(), {tile, tile}, tex->getCords());
	}
	void Renderer2D::draw(const Transform& transform, const shdPtr<SubTex2D>& tex, const glm::vec4 color, float tile){
		drawInt(transform.getMat(), color, tex->getTex(), {tile,tile}, tex->getCords());
	}
	void Renderer2D::draw(const Transform& transform, const shdPtr<SubTex2D>& tex, const glm::vec4 color, glm::vec2 tile){
		drawInt(transform.getMat(), color, tex->getTex(), tile, tex->getCords());
	}

	void Renderer2D::drawInt(glm::mat4x4 transform, const glm::vec4 color, const shdPtr<Texture2D>& tex, glm::vec2 tile, glm::vec2* texCords){

		float texIndex = -1.0f;

		for(int i = 0; i < data.texSlotInd; i++){
			auto& obj = *data.texSlots[i].get();
			if(obj == *tex.get()){
				texIndex = (float)i;
				break;
			}
		}

		if(texIndex == -1.0f){
			texIndex = (float)data.texSlotInd;
			data.texSlots[data.texSlotInd] = tex; 
			data.texSlotInd++;
		}

		if(texCords == nullptr){
			data.vertPtr->pos = transform * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
			data.vertPtr->color = color;
			data.vertPtr->texCord = {0.0f, 0.0f};
			data.vertPtr->texIndex = texIndex;
			data.vertPtr->tile = tile;
			data.vertPtr++;

			data.vertPtr->pos = transform * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);
			data.vertPtr->color = color;
			data.vertPtr->texCord = {1.0f, 0.0f};
			data.vertPtr->texIndex = texIndex;
			data.vertPtr->tile = tile;
			data.vertPtr++;

			data.vertPtr->pos = transform * glm::vec4(0.5f, 0.5f, 0.0f, 1.0f);
			data.vertPtr->color = color;
			data.vertPtr->texCord = {1.0f, 1.0f};
			data.vertPtr->texIndex = texIndex;
			data.vertPtr->tile = tile;
			data.vertPtr++;

			data.vertPtr->pos = transform * glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f);
			data.vertPtr->color = color;
			data.vertPtr->texCord = {0.0f, 1.0f};
			data.vertPtr->texIndex = texIndex;
			data.vertPtr->tile = tile;
			data.vertPtr++;
		}else{
			data.vertPtr->pos = transform * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
			data.vertPtr->color = color;
			data.vertPtr->texCord = *texCords;
			data.vertPtr->texIndex = texIndex;
			data.vertPtr->tile = tile;
			data.vertPtr++;

			data.vertPtr->pos = transform * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);
			data.vertPtr->color = color;
			data.vertPtr->texCord = *(texCords + 1);
			data.vertPtr->texIndex = texIndex;
			data.vertPtr->tile = tile;
			data.vertPtr++;

			data.vertPtr->pos = transform * glm::vec4(0.5f, 0.5f, 0.0f, 1.0f);
			data.vertPtr->color = color;
			data.vertPtr->texCord = *(texCords + 2);
			data.vertPtr->texIndex = texIndex;
			data.vertPtr->tile = tile;
			data.vertPtr++;

			data.vertPtr->pos = transform * glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f);
			data.vertPtr->color = color;
			data.vertPtr->texCord = *(texCords + 3);
			data.vertPtr->texIndex = texIndex;
			data.vertPtr->tile = tile;
			data.vertPtr++;
		}
		data.indCount+=6;
		if(data.indCount == data.maxInds){
			drawToScreen();
		}

		//data.texShader->setValue("tile", tile);
		//data.texShader->setValue("tex", 0);
		//data.vertArray->bind();
		//tex->bind();
		//glDrawElements(GL_TRIANGLES, data.vertArray->getIndBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}
}