#include "AnimationController.h"
#include "GameFramework\GameContent\Animation.h"
#include "GameFramework\GameObject\GameObject.h"
#include "Main\GameSystem.h"
#include "GameFramework\GameContent\Sprite.h"
#include "GameFramework\GameContent\Texture.h"

AnimationController::AnimationController(std::vector<Animation*> animation, int sortingOrder, const std::string& name, ARGB color) :
	Component(name),
	AnimationCollection(animation),
	sortingOrder(sortingOrder),
	currentAnimation(nullptr),
	color(color),
	isActive(1),
	paused(0),
	currentSprite(nullptr),
	hasBeenLooped(0)
{
}


AnimationController::~AnimationController()
{
}

void AnimationController::SetColor(const ARGB & color)
{
	this->color = color;
}

void AnimationController::SetActive(bool active)
{
	this->isActive = active;
}

void AnimationController::Pause(bool paused)
{
	this->paused = paused;
}

Animation * AnimationController::AddMainAnimation(Animation * animation)
{
	Animation* newAnim = new Animation(animation->sprites, animation->timePerFrame, animation->looped, animation->GetName());
	AnimationCollection.push_back(newAnim);
	currentAnimation = newAnim;
	return newAnim;
}

Animation * AnimationController::AddAnimation(Animation * animation)
{
	Animation* newAnim = new Animation(animation->sprites, animation->timePerFrame, animation->looped, animation->GetName());
	AnimationCollection.push_back(newAnim);
	return newAnim;
}

void AnimationController::OnSpawn()
{
	currentSprite = currentAnimation->GetActiveSprite();
}

void AnimationController::LateUpdate()
{
	if (isActive == 0) return;
	if (!currentAnimation) return;
	if (paused == 0)
	{
		currentAnimation->PlayBack();
		currentSprite = currentAnimation->GetActiveSprite();
	}
	if (!currentSprite) return;
	GameSystem::Draw(
		gameObject->GetTransform(),
		currentSprite->GetTexture()->GetObjectID(),
		currentSprite->GetRect(),
		currentSprite->GetPixelsPerUnit(),
		sortingOrder,
		color);
}



