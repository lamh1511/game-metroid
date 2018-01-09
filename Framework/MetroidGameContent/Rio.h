#pragma once
#include "Enemy.h"

class Rio : public Enemy
{
public:
	Rio();
	virtual ~Rio();

	virtual void OnSpawn() override;
	virtual void Update() override;

	virtual void OnCollisionEnter(GameObject * other, const Vec2& normal = Vec2()) override;

	Vec2 rightDownVelo;
	Vec2 leftDownVelo;
	Vec2 rightUpVelo;
	Vec2 leftUpVelo;

	Vec2 _rightDownVelo;
	Vec2 _leftDownVelo;
	Vec2 _rightUpVelo;
	Vec2 _leftUpVelo;


	float deacceleration;
	float acceleration;
	int state;
	int flag;
};

