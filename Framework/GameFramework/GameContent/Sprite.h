#pragma once
#include "GameFramework\Object.h"

class Texture;

class Sprite final : public Object
{
public:
	Sprite();
	Sprite(Texture* texture, const Rect& srcRect, float pixelsPerUnit, const std::string& name);
	~Sprite();
public:
	const Rect& GetRect() const;
	float GetPixelsPerUnit();
	Texture* GetTexture();

	//static bool LoadSpriteFromFile(const std::string& fileName);
protected:
	Texture* texture;
	Rect srcRect;
	float pixelsPerUnit;
};

