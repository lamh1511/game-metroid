#pragma once
#include "GameFramework\GameObject\GameObject.h"

class MetroidCharacter;

class Bomb : public GameObject
{
public:
	Bomb();
	virtual ~Bomb();

	virtual void Update() override;
	virtual void OnSpawn() override;

	void DestroyBlock();

	double lifeTime;
	int damage;
	double explosionTime;
	MetroidCharacter* Samus;
	SimulatePhysics* physics;
	AnimationController* animation;

	virtual void OnCollisionEnter(GameObject * other, const Vec2& normal = Vec2()) override;

	void (Bomb::*UpdateState)();
	void CountDown();
	void Explode();
};

