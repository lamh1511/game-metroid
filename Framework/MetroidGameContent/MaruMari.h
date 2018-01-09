#pragma once
#include "GameFramework\GameObject\GameObject.h"

class MaruMari : public GameObject
{
public:
	MaruMari();
	virtual ~MaruMari();

	virtual void OnCollisionEnter(GameObject * other, const Vec2& normal = Vec2()) override;
	virtual void OnSpawn() override;
	virtual void Update() override;
};

