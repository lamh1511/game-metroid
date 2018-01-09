#pragma once
#include "GameFramework\GameComponent\Component.h"
#include "CameraComponent.h"
#include "AnimationController.h"
#include "SimulatePhysics.h"
#include "SpriteRenderer.h"
#include <vector>
#include "GameFramework\GameContent\Animation.h"

class Sprite;
class Animation;

class AnimationController : public Component
{
public:
	AnimationController(std::vector<Animation*> animation = std::vector<Animation*>(), int sortingOrder = 0, const std::string& name = "None", ARGB color = ARGB(255, 255, 255, 255));
	virtual ~AnimationController();
	void SetColor(const ARGB& color);
	void SetActive(bool active);
	void Pause(bool paused);
	Animation* AddMainAnimation(Animation* animation);
	Animation* AddAnimation(Animation* animation);
	ARGB color;
	Animation* currentAnimation;
	int sortingOrder;
protected:
	std::vector<Animation*> AnimationCollection;
	bool isActive;
	bool hasBeenLooped;
protected:
	bool paused;
	Sprite * currentSprite;
	virtual void OnSpawn() override;
	virtual void LateUpdate() override;
};

