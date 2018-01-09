#pragma once
#include "GameFramework\GameComponent\AnimationController.h"
#include "Kraid.h"

class KraidAnimation : public AnimationController
{
public:
	KraidAnimation();
	virtual ~KraidAnimation();

	Animation* idle;
	Animation* jump;
	Animation* damagedIdle;
	Animation* damagedJump;
	Kraid* ridley;

	virtual void OnSpawn() override;
	virtual void Update() override;
};

