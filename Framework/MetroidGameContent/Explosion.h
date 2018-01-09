#pragma once
#include "GameFramework\GameObject\GameObject.h"

class Explosion :
	public GameObject
{
public:
	Explosion();
	virtual ~Explosion();

	virtual void LateUpdate() override;

	Animation* explosion;
};

