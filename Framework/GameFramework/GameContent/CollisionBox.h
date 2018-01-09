#pragma once
class CollisionBox
{
public:
	CollisionBox();
	CollisionBox(float x, float y, float width, float height);
	~CollisionBox();
public:
	float x, y, width, height;
};

