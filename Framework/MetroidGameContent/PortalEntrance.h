#pragma once
#include "GameFramework\GameObject\GameObject.h"

class Portal;

class PortalEntrance : public GameObject
{
public:
	PortalEntrance(bool isRedPortal = 0);
	virtual ~PortalEntrance();

	Animation* open;
	Animation* close;
	Animation* normal;
	virtual void OnCollisionEnter(GameObject * other, const Vec2& normal) override;
	virtual void Update() override;
	AnimationController* animation;
	SimulatePhysics* physics;

	bool isRedPortal;
	double openTime;
	friend class Portal;
};

