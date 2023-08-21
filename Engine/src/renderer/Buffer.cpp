#include "Buffer.h"
namespace Engine{
	VertBuffer::VertBuffer(float* verts, unsigned int size){
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, size, verts, GL_STATIC_DRAW);
	}
	VertBuffer::~VertBuffer(){
		glDeleteBuffers(1, &id);
	}
	void VertBuffer::setData(){
		
	}
	void VertBuffer::bind(){
		glBindBuffer(1, id);
	}
	void VertBuffer::unbind(){

	}
	void VertBuffer::setLayout(BufferLayout _layout){layout = _layout;}

	IndBuffer::IndBuffer(unsigned int* inds, unsigned int ct){
		glGenBuffers(1, &id);
		count = ct;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, ct * sizeof(unsigned int), inds, GL_STATIC_DRAW);
	}
	IndBuffer::~IndBuffer(){
		glDeleteBuffers(1, &id);
	}
	void IndBuffer::setData(){
		
	}
	void IndBuffer::bind(){
		glBindBuffer(1, id);
	}
	void IndBuffer::unbind(){

	}
	int IndBuffer::getCount(){
		return count;
	}
}