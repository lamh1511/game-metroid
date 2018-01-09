#pragma once
#include "GameFramework\GameComponent\AnimationController.h"
#include "Bumerang.h"

class BumerangAnimation : public AnimationController
{
public:
	BumerangAnimation();
	virtual ~BumerangAnimation();

	Animation* anim;
	//RidleyBullet* ridleybullet;
	int waiting;

	virtual void OnSpawn() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};