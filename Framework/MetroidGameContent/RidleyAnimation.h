#pragma once
#include "GameFramework\GameComponent\AnimationController.h"
#include "Ridley.h"

class RidleyAnimation : public AnimationController
{
public:
	RidleyAnimation();
	virtual ~RidleyAnimation();

	Animation* idle;
	Animation* jump;
	Animation* damagedIdle;
	Animation* damagedJump;
	Animation* dead;
	Ridley* ridley;

	virtual void OnSpawn() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

	//void Idle();
	//void Jump();
};

