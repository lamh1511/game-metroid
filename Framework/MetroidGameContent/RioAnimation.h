#pragma once
#include "GameFramework\GameComponent\AnimationController.h"
class RioAnimation :
	public AnimationController
{
public:
	RioAnimation();
	virtual ~RioAnimation();

	Animation* mainAnim;

	virtual void OnSpawn() override;
};

