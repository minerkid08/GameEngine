#include "Texture.h"
#include "Core/Log.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stbImage.h>
#include <glad/glad.h>
namespace Engine{
	Texture2D::Texture2D(const std::string& filename){
		path = filename;
		int channels;
		int _width;
		int _height;
		stbi_set_flip_vertically_on_load(1);
		unsigned char* data = stbi_load(filename.c_str(), &_width, &_height, &channels, 0);
		width = _width;
		height = _height;
		if(data == nullptr){
			Log::Error("Failed to load image: " + filename);
		}
		glCreateTextures(GL_TEXTURE_2D, 1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTextureStorage2D(id, 1, (channels == 4 ? GL_RGBA8 : GL_RGB8), width, height);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureSubImage2D(id, 0, 0, 0, width, height, (channels == 4 ? GL_RGBA : GL_RGB), GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}
	Texture2D::~Texture2D(){
		glDeleteTextures(1, &id);
	}
	void Texture2D::bind(unsigned int slot){
		glBindTextureUnit(slot, id);
	}
}