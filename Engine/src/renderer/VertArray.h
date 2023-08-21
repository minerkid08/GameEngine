#pragma once
#include <glad/glad.h>
#include <memory>
#include "Buffer.h"

namespace Engine{
	class API VertArray{
		public:
		VertArray();
		~VertArray();
		void bind();
		void addVertBuffer(shdPtr<VertBuffer>& buffer);
		void setIndBuffer(shdPtr<IndBuffer>& buffer);
		const std::vector<shdPtr<VertBuffer>>& getVertBuffers() {return vertBuffers;}
		const shdPtr<IndBuffer>& getIndBuffer() {return indBuffer;}
		private:
		std::vector<shdPtr<VertBuffer>> vertBuffers;
		shdPtr<IndBuffer> indBuffer;
		unsigned int id;
	};
}