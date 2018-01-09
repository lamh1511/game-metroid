#pragma once
#include "MetroidGameContent\SamusDamage.h"


class SamusWaveBeam : public SamusDamage
{
public:
	SamusWaveBeam(const Vec2& direction = Vec2(1.0f, 0), const Vec2& position = Vec2(0, 0));

	virtual ~SamusWaveBeam();
	virtual void Update() override;
	virtual void OnSpawn() override;
	virtual void OnCollisionEnter(GameObject* other, const Vec2& normal = Vec2()) override;
	double x, y, A;
	double yMax;
	float speedX, speedY;
	void (SamusWaveBeam::*Move)();
	void MoveUp();
	void MoveRight();
	void MoveLeft();
};

