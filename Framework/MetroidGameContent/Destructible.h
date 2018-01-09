#pragma once
#include "GameFramework\GameObject\GameObject.h"

#define RELIVE_TIME 5.0

class Destructible : public GameObject
{
public:
	Destructible();
	virtual ~Destructible();
	void (Destructible::*UpdateState)();
	void CountDown();
	void VoidFunc();
	void DestroySelf();
	virtual void OnSpawn() override;
	virtual void Update() override;
	virtual void OnCollisionEnter(GameObject* other, const Vec2& normal = Vec2()) override;
	SimulatePhysics* physics;
	double relive;
	int idBlock;
};

