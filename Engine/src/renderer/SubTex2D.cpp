#include "SubTex2D.h"
#include "Core/Log.h"
namespace Engine{
	SubTex2D::SubTex2D(const shdPtr<Texture2D>& _tex, const glm::vec2& texSize, const glm::vec2& texPos){
		tex = _tex;
		texCords[0] = {(texPos.x *       texSize.x) / tex->getWidth(), (texPos.y *       texSize.y) / tex->getHeight()};
		texCords[1] = {((texPos.x + 1) * texSize.x) / tex->getWidth(), (texPos.y *       texSize.y) / tex->getHeight()};
		texCords[2] = {((texPos.x + 1) * texSize.x) / tex->getWidth(), ((texPos.y + 1) * texSize.y) / tex->getHeight()};
		texCords[3] = {(texPos.x *       texSize.x) / tex->getWidth(), ((texPos.y + 1) * texSize.y) / tex->getHeight()};
	}
}