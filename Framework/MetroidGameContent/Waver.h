#pragma once
#include "MetroidGameContent\Enemy.h"
class Waver :
	public Enemy
{
public:
	Waver();
	virtual ~Waver();

	virtual void OnSpawn() override;
	virtual void Update() override;


	virtual void OnCollisionEnter(GameObject * other, const Vec2& normal = Vec2()) override;
	

	float moveRightVelo;
	float moveLeftVelo;
	float moveDownVelo;
	float moveUpVelo;

	bool isMoveLeft;
	bool isMoveRight;
	bool isMoveDown;
	bool isMoveUp;

	int flag;

	float deceleration;
	float acceleration;
	double countTime;

	float upRange;
	float lowRange;

	Vec2 scale;
};

