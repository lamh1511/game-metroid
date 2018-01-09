#pragma once
#include "Enemy.h"

class Zeb :
	public Enemy
{
public:
	Zeb();
	virtual ~Zeb();

	virtual void OnSpawn() override;
	virtual void Update() override;


	//Vec2 body;
	//float vx;
	//float vy;

	virtual void OnCollisionEnter(GameObject * other, const Vec2& normal = Vec2()) override;
	
	float moveRightVelo;
	float moveLeftVelo;
	Vec2 startPosition;
	int flag;

	double delayTime;
	double countTime;
	double lifeTime;

	float scale;
};

