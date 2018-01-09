#pragma once
#include "Enemy.h"
class Ripper :
	public Enemy
{
public:
	Ripper();
	virtual ~Ripper();

	virtual void OnSpawn() override;
	virtual void Update() override;



	virtual void OnCollisionEnter(GameObject * other, const Vec2& normal = Vec2()) override;

	bool isMoveLeft;
	bool isMoveRight;

	float moveLeftVelo;
	float moveRightVelo;

	float scale;
};

