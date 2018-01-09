#include "SpriteRenderer.h"
#include "Main\GameSystem.h"
#include "GameFramework\GameObject\GameObject.h"
#include "GameFramework\GameContent\Sprite.h"
#include "GameFramework\GameContent\Texture.h"


SpriteRenderer::SpriteRenderer(Sprite * sprite, int sortingOrder, const std::string & name) :
	Component(name),
	sprite(sprite),
	sortingOrder(sortingOrder),
	color(ARGB(255, 255, 255, 255)),
	active(1)
{
}


SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::SetSprite(Sprite * sprite)
{
	this->sprite = sprite;
}

void SpriteRenderer::SetDrawOrder(int drawOrder)
{
	this->sortingOrder = drawOrder;
}

void SpriteRenderer::SetColor(const ARGB & color)
{
	this->color = color;
}

void SpriteRenderer::SetActive(bool active)
{
	this->active = active;
}

bool SpriteRenderer::IsActive()
{
	return active;
}

void SpriteRenderer::LateUpdate()
{
	if (active == 0) return;
	GameSystem::Draw(
		gameObject->GetTransform(),
		sprite->GetTexture()->GetObjectID(),
		sprite->GetRect(),
		sprite->GetPixelsPerUnit(),
		this->sortingOrder,
		color);
}
