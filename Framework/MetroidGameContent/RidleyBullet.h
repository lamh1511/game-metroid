#pragma once
#include "Enemy.h"


class RidleyBullet : public Enemy
{
public:
	RidleyBullet();
	virtual ~RidleyBullet();

	
	void Fire(const Vec2& firePosition, const Vec2& direction);
	virtual void Update() override;
	virtual void OnSpawn() override; //*
	virtual void OnCollisionEnter(GameObject* other, const Vec2& normal = Vec2()) override;
	double lifeTime;
	double x, y, A;
	double yMax;
	float speedX, speedY;

	GameObject* ridley;
	Vec2 ridleyPos;
};

