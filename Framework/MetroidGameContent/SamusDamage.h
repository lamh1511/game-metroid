#pragma once
#include "GameFramework\GameObject\GameObject.h"

class MetroidCharacter;

class SamusDamage : public GameObject
{
public:
	SamusDamage() {};
	SamusDamage(const Vec2& position, const Vec2& direction, void (SamusDamage::*Type)());
	virtual ~SamusDamage() {};

	double lifeTime;
	int damage;
	float speed;
	SimulatePhysics* physic;
	SpriteRenderer* sprite;
	MetroidCharacter* Samus;
	virtual void OnSpawn() override;
	virtual void Update() override;
	virtual void OnCollisionEnter(GameObject* other, const Vec2& normal = Vec2()) override;
public:
	void IceBeam();
	void MissileRocket();
	void LongBeam();
	void SamusBomb();
	void WaveBeam();
	void NormalBeam();

	void (SamusDamage::*Type)();
};

