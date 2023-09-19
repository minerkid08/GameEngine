#pragma once
#include <string>
#include "Core/Core.h"
namespace Engine{
	class Texture{
		public:
		virtual int getWidth(){return 0;}
		virtual int getHeight(){return 0;}
		virtual void bind(unsigned int slot = 0){}
	};
	class API Texture2D : public Texture{
		public:
		Texture2D(const std::string& filename);
		Texture2D(int width, int height);
		void setData(void* data, int size);
		~Texture2D();
		int getWidth(){return width;}
		int getHeight(){return height;}
		void bind(unsigned int slot = 0);
		int getId() const {return id;}

		bool operator==(const Texture2D& other) const {return id == other.getId();}

		private:
		unsigned int id;
		unsigned int width = 0;
		unsigned int height = 0;
		std::string path;
		int intFormat;
		int format;
	};
}