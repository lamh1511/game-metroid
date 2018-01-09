#pragma once
#include "GameFramework\GameComponent\Component.h"

class Sprite;

class SpriteRenderer final : public Component
{
public:
	SpriteRenderer(Sprite* sprite = nullptr, int sortingOrder = 0, const std::string& name = "None");
	~SpriteRenderer();
public:
	void SetSprite(Sprite* sprite);
	void SetDrawOrder(int drawOrder);
	void SetColor(const ARGB& color);
	void SetActive(bool active);
	bool IsActive();
protected:
	void LateUpdate() override;
	int sortingOrder;
	Sprite* sprite;
	ARGB color;
	bool active;
};