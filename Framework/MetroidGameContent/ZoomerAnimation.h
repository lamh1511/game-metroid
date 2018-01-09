#pragma once
#include "GameFramework\GameComponent\AnimationController.h"
class Zoomer;

class ZoomerAnimation : public AnimationController
{
public:
	ZoomerAnimation();
	virtual ~ZoomerAnimation();
	Zoomer* zoomer;
	Animation* mainAnim;

	virtual void OnSpawn() override;
	/*virtual void Update() override;
	virtual void LateUpdate() override;*/
	friend class Zoomer;
};

