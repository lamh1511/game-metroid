#pragma once
#include "Enemy.h"


class Bumerang : public Enemy
{
public:
	Bumerang();
	virtual ~Bumerang();

	void Fire(const Vec2& firePosition, int direction);
	virtual void Update() override;
	virtual void OnSpawn() override; //*
	virtual void OnCollisionEnter(GameObject* other, const Vec2& normal = Vec2()) override;
	double lifeTime;
	double x, y, A;
	double yMax;
	float speedX, speedY;
	Vec2 firePosition;
	int direction;

	double shootingTimer;
	float timeout;
	int shoot;

	GameObject* kraid;
	Vec2 kraidPos;

	float xpos, ypos;
};

