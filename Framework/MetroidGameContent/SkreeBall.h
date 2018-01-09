#pragma once
//#include "GameFramework\GameObject\GameObject.h"
#include "Enemy.h"
class SkreeBall : public Enemy
{
public:
	SkreeBall();
	virtual ~SkreeBall();
	float speed;
	void SetAngle(float angle);
	virtual void Update() override;
	virtual void OnCollisionEnter(GameObject * other, const Vec2& normal = Vec2()) override;

	static void Explose(const Vec2& position, Scene *scene);
	double lifeTime;
	float angle;
};

