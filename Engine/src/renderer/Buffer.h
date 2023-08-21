#pragma once
#include "../Log.h"
#include "../Core.h"
#include <vector>
#include <string>
#include <initializer_list>
#include <glad/glad.h>
namespace Engine{
	enum ShaderType{
		ShaderTypeNone = 0,
		Int,Int2,Int3,Int4,
		Float,Float2,Float3,Float4,
		Mat2,Mat3,Mat4,
		Bool
	};
	static unsigned int ShaderTypeSize(ShaderType type){
		switch(type){
			case ShaderTypeNone: return 0;
			case Int: return sizeof(int);
			case Int2: return sizeof(int) * 2;
			case Int3: return sizeof(int) * 3;
			case Int4: return sizeof(int) * 4;
			case Float: return sizeof(float);
			case Float2: return sizeof(float) * 2;
			case Float3: return sizeof(float) * 3;
			case Float4: return sizeof(float) * 4;
			case Mat2: return sizeof(float) * 2 * 2;
			case Mat3: return sizeof(float) * 3 * 3;
			case Mat4: return sizeof(float) * 4 * 4;
			case Bool: return sizeof(bool);
		}
		Log::Error("Unknown shader type: " + std::to_string(type));
		return 0;
	}
	struct API BufferElem{
		std::string name;
		ShaderType type;
		uint32_t offset;
		unsigned int size;
		bool normalized = false;
		BufferElem(){}
		BufferElem(ShaderType _type, const char* _name) : type(_type), size(ShaderTypeSize(_type)), offset(0){
			std::string str(_name);
			name = str;
		}
		int getElementCount() const {
			switch(type){
				case ShaderTypeNone: return 0;
				case Int: return 1;
				case Int2: return 2;
				case Int3: return 3;
				case Int4: return 4;
				case Float: return 1;
				case Float2: return 2;
				case Float3: return 3;
				case Float4: return 4;
				case Mat2: return 2 * 2;
				case Mat3: return 3 * 3;
				case Mat4: return 4 * 4;
				case Bool: return 1;
			}
			return 0;
		}
		int getElementType() const {
			switch(type){
				case ShaderTypeNone: return 0;
				case Int: return GL_INT;
				case Int2: return GL_INT;
				case Int3: return GL_INT;
				case Int4: return GL_INT;
				case Float: return GL_FLOAT;
				case Float2: return GL_FLOAT;
				case Float3: return GL_FLOAT;
				case Float4: return GL_FLOAT;
				case Mat2: return GL_FLOAT;
				case Mat3: return GL_FLOAT;
				case Mat4: return GL_FLOAT;
				case Bool: return GL_BOOL;
			}
			return 0;
		}
	};
	class API BufferLayout{
		public:
		BufferLayout(const std::initializer_list<BufferElem>& elem) : elements(elem){calculateOffsets();}
		BufferLayout(){}
		inline const std::vector<BufferElem>& getElements(){return elements;}
		std::vector<BufferElem>::iterator begin(){return elements.begin();}
		std::vector<BufferElem>::iterator end(){return elements.end();}
		std::vector<BufferElem>::const_iterator begin() const {return elements.begin();}
		std::vector<BufferElem>::const_iterator end() const {return elements.end();}
		unsigned int stride;
		private:
		void calculateOffsets(){
			stride = 0;
			int offset = 0;
			int i = 0;
			for(BufferElem& elem : elements){
				elem.offset = offset;
				stride += elem.size;
				offset += elem.size;
				i++;
			}
		}
		std::vector<BufferElem> elements;
	};
	class API VertBuffer{
		public:
		VertBuffer(float* verts, unsigned int size);
		~VertBuffer();
		void bind();
		void unbind();
		void setData();
		void setLayout(BufferLayout _layout);
		BufferLayout getLayout(){return layout;}
		private:
		BufferLayout layout;
		unsigned int id;
	};
	class API IndBuffer{
		public:
		IndBuffer(unsigned int* inds, unsigned int ct);
		~IndBuffer();
		void bind();
		void unbind();
		void setData();
		int getCount();
		private:
		unsigned int id;
		unsigned int count;
	};
}