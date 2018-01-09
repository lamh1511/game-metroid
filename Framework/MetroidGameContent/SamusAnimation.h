#pragma once
#include "GameFramework\GameComponent\AnimationController.h"

class MetroidCharacter;

class SamusAnimation : public AnimationController
{
public:
	SamusAnimation();
	virtual ~SamusAnimation();

	virtual void OnSpawn() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

	inline void Idle();
	inline void Run();
	inline void Roll();
	inline void Jump();
	inline void Rotate();

	inline void AimUp();
	inline void ShootUp();
	inline void RunShootForward();
	inline void JumpShootUp();
	inline void JumpShootForward();
	inline void RunShootUp();

	void LockCurrentState(bool locked);

	Vec2 playerVelocity;

	Animation* idle;
	Animation* run;
	Animation* jump;
	Animation* roll;
	Animation* rotate;
	Animation* aimup;
	Animation* shootup;

	Animation* runshootforward;
	Animation* jumpshootup;
	Animation* jumpshootforward;
	Animation* runshootup;

	float maxJumpSpeed;
	float jumpSpeed;
	double jumpTime;

	bool stateLocked;
	SimulatePhysics* physic;

	MetroidCharacter* Samus;
	friend class MetroidCharacter;

	void (SamusAnimation::*RollFunc)();
	void SamusAnimation::Roll_0();
	void SamusAnimation::Roll_1();

	void EnableRolling();
	Vec2 RollingBodySize;
};

