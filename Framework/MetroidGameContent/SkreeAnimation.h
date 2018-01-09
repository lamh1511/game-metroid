#pragma once
#include "GameFramework\GameComponent\AnimationController.h"

class SkreeAnimation : public AnimationController
{
public:
	SkreeAnimation();
	virtual ~SkreeAnimation();

	Animation* mainAnim;

	virtual void OnSpawn() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

