#pragma once
#include "GameFramework\GameObject\GameObject.h"

class MetroidCharacter;

class Enemy : public GameObject
{
public:
	Enemy();
	virtual ~Enemy() {};

	int Health;
	int Damage;
	double OnGetDamageDelayTime;
	Vec2 position;
	float vx;
	float vy;
	bool isFrozen;
	double freezeTime;

	SimulatePhysics* physics;
	AnimationController* animation;
	MetroidCharacter* Samus;

	int CheckTopTile(Vec2&);
	int CheckBottomTile(Vec2&);
	int CheckLeftTile(Vec2&);
	int CheckRightTile(Vec2&);
	virtual void OnCollisionEnter(GameObject * other, const Vec2& normal = Vec2()) override;
	virtual void OnSpawn() override;
	virtual void Update() override;

	void Freeze();
};

