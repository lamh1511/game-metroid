#pragma once
#include "GameFramework\GameComponent\AnimationController.h"
#include "RidleyBullet.h"

class RidleyBulletAnimation : public AnimationController
{
public:
	RidleyBulletAnimation();
	virtual ~RidleyBulletAnimation();

	Animation* anim;
	//RidleyBullet* ridleybullet;
	int waiting;

	virtual void OnSpawn() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

