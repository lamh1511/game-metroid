#pragma once
#include "GameFramework\GameComponent\Component.h"
#include <vector>

class SimulatePhysics final : public Component
{
public:
	SimulatePhysics(const Vec2& bodySize = Vec2(0, 0), const Vec2& velocity = Vec2(0, 0));
	~SimulatePhysics();
public:
	void SetBodySize(const Vec2& bodySize);
	const Vec2& GetBodySize();
	const RectF& GetBodyRect();
	void SetVelocity(const Vec2& velocity);
	void SetVelocityX(float vx);
	void SetVelocityY(float vy);
	const Vec2& GetVelocity();
	void SetMass(float mass);
	void SetStatic(bool isStatic);
	bool IsTrigger();
	void DisableCollision(bool isTrigger);
	static bool IsColliding(const RectF& bodyRect, const RectF& otherRect);
	
public:
	inline void HandleCollision(std::vector<SimulatePhysics*>& others);
private:
	inline float SweptAABB(SimulatePhysics* other, float& normalx, float& normaly);
	inline RectF GetSweptBroadphaseBox();
	
protected:
	void OnSpawn() override;
	void Update() override;
	void LateUpdate() override;
	RectF bodyRect;
	Vec2 bodySize;
	Vec2 velocity;
	float mass;
	bool isStatic;

	Vec2 normal;
	bool isTrigger;
	float collisionTimeLeft;
	float collisionTimeRight;
	float collisionTimeTop;
	float collisionTimeBottom;
};

