#include "Sprite.h"
#include "GameFramework\GameContent\Texture.h"


Sprite::Sprite()
{
}

Sprite::Sprite(Texture * texture, const Rect& srcRect, float pixelsPerUnit, const std::string& name):
	Object(name),
	texture(texture),
	srcRect(srcRect),
	pixelsPerUnit(pixelsPerUnit)
{
}


Sprite::~Sprite()
{
}

const Rect & Sprite::GetRect() const
{
	return this->srcRect;
}

float Sprite::GetPixelsPerUnit()
{
	return this->pixelsPerUnit;
}

Texture * Sprite::GetTexture()
{
	return this->texture;
}
