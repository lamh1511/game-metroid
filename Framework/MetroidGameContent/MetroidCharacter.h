#pragma once
#include "GameFramework\GameObject\GameObject.h"
#include "SamusDamage.h"

class SamusAnimation;

#define SHOOTDELAYTIME 0.12
#define SHOOTDELAYTIME_ICEBEAM 0.2
#define SHOOTDELAYTIME_ROCKET 0.5
#define SHOOTDELAYTIME_WAVEBEAM 0.3
#define SAMUSBODYSIZE Vec2(0.8f, 2.0f)
#define ROLLINGBODYSIZE Vec2(0.8f, 0.8f)

class MetroidCharacter : public GameObject
{
public:
	MetroidCharacter();
	virtual ~MetroidCharacter();

	SpriteRenderer* OnDamageSprite;
	CameraComponent* CharacterCamera;
	SimulatePhysics* CharacterPhysics;
	SamusAnimation* animation;
	void (SamusDamage::*WeaponType)(); // phai include SamusDamage.h de tranh crash
	void Fire(const Vec2& direction);
	float moveSpeed;
	float jumpSpeed;
	double jumpTime;
	bool canShoot;
	bool missileRocketEnabled;
	bool bombEnabled;
	bool longBeamEnabled;
	double shootDelayTime;
	bool DisableInput;
	int rocketCount;
	int energyTankCount;
	GameObject* camera;
	virtual void OnSpawn() override;
	virtual void Update() override;
	void Teleport();
	virtual void OnCollisionEnter(GameObject* other, const Vec2& normal = Vec2()) override;
	virtual void LateUpdate() override;
	bool OnDamage;

	double OnDamageTime;
	friend class SamusAnimation;

	int energy;
};



