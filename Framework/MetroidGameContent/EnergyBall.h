#pragma once
#include "GameFramework\GameObject\GameObject.h"

class EnergyBall : public GameObject
{
public:
	EnergyBall();
	virtual ~EnergyBall();

	virtual void Update() override;
	virtual void OnCollisionEnter(GameObject * other, const Vec2& normal) override;

	double lifeTime;
};

