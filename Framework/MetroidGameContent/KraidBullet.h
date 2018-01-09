#pragma once
#include "Enemy.h"


class KraidBullet : public Enemy
{
public:
	KraidBullet();
	virtual ~KraidBullet();

	GameObject* kraid;

	void Fire(const Vec2 & firePosition, float direction);
	virtual void Update() override;
	virtual void OnSpawn() override; //*
	virtual void OnCollisionEnter(GameObject* other, const Vec2& normal = Vec2()) override;
	Vec2 kraidPos;
	Vec2 firePosition;
	double x, lifeTime, shootingTimer;
	float timeout;
	float speedX, direction;
	int shoot;
};