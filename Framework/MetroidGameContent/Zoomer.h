#pragma once
#include "Enemy.h"
class Spawner;

class ZoomerAnimation;

class Zoomer : public Enemy
{
public:
	Zoomer();
	virtual ~Zoomer() {};
	virtual void OnSpawn() override;
	virtual void Update() override;
	virtual void OnCollisionEnter(GameObject * other, const Vec2& normal = Vec2()) override;
	
	inline void getNewEndPoint(Vec2&, int&);
	inline void getNewEndPoint2(Vec2&, int&);
	Vec2 position;
	Vec2 endpoint;
	Vec2 endpoint2;
	
	int rotate;

	void (Zoomer::*ZoomerUpdate)();
	void Zoomer1();
	void Zoomer2();
	Zoomer* SetZoomerType(int type);
	friend class Spawner;
};

