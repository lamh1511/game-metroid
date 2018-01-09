#pragma once
#include "GameFramework\GameObject\GameObject.h"
#include "MetroidCharacter.h"

class Ridley : public GameObject 
{
public:
	Ridley();
	virtual ~Ridley();
	virtual void OnSpawn() override;
	virtual void Update() override;
	virtual void OnCollisionEnter(GameObject * other, const Vec2& normal = Vec2()) override;
	SpriteRenderer* sprite;
	SimulatePhysics* physics;
	AnimationController* animation;
	MetroidCharacter* Samus;
	Vec2 ridley;
	int flag;
	double countTime, damagedTimer;
	float vx, vy;
	double maxH;
	int rotate;
	int waiting;
	bool isDead;
	double deadTimer;
	int Damage;
	double hp; // hp
	int damaged, damagedIdle, damagedJump;

	void(*RidleyUpdate)(Ridley* gameObject);
	void moveState();
	int checkBottomTile(Vec2 body);
	int checkTopTile(Vec2 body);
	int checkDamaged(int isDamaged);
	void resetNoDamage();
	int checkSamusGun(int samusGun);
};