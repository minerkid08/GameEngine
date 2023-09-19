#pragma once
#include <glm/glm.hpp>
#include "Texture.h"

namespace Engine{
	class API SubTex2D{
		public:
		SubTex2D(const shdPtr<Texture2D>& _tex, const glm::vec2& texSize, const glm::vec2& texPos);
		shdPtr<Texture2D> getTex(){return tex;}
		glm::vec2* getCords(){return texCords;}
		private:
		shdPtr<Texture2D> tex;
		glm::vec2 texCords[4];
	};
}