#include "VertArray.h"

namespace Engine{
	VertArray::VertArray(){
		glGenVertexArrays(1, &id);
		glBindVertexArray(id);
	}
	VertArray::~VertArray(){
		glDeleteVertexArrays(1, &id);
	}
	void VertArray::bind(){
		glBindVertexArray(id);
	}
	void VertArray::setIndBuffer(shdPtr<IndBuffer>& buffer){
		glBindVertexArray(id);
		buffer->bind();
		indBuffer = buffer;
	}
	void VertArray::addVertBuffer(shdPtr<VertBuffer>& buffer){
		glBindVertexArray(id);
		buffer->bind();
		if(buffer->getLayout().getElements().size() == 0){
			Log::Error("Vertex buffer layout has no elements");
		}
		int i = 0;
		const BufferLayout& layout = buffer->getLayout();
		for(const BufferElem& elem : layout){
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, elem.getElementCount(), elem.getElementType(), elem.normalized ? GL_TRUE : GL_FALSE, layout.stride, (const void*)elem.offset);
			i++;
		}
		vertBuffers.push_back(buffer);
	}
}