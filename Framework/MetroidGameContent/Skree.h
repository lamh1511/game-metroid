#pragma once
#include "Enemy.h"

class Skree : public Enemy
{
public:
	Skree();
	virtual ~Skree();

	virtual void OnSpawn() override;
	virtual void Update() override;
	virtual void OnCollisionEnter(GameObject * other, const Vec2& normal = Vec2()) override;
	int flag1, flag2;

	double DestroyDelayTime;
};

