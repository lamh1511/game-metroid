#pragma once
#include "GameFramework\Object.h"
#include <vector>

class Sprite;

class Animation final : public Object
{
public:
	Animation();
	Animation(std::vector<Sprite*> sprites, double timePerFrame, bool looped = true, const std::string& name = "None");
	~Animation();
public:
	bool PlayBack();
	void Reset();
	Sprite* GetActiveSprite();
public:
	std::vector<Sprite*> sprites;

	double timePerFrame;
	double currentTotalTime;
	int currentIndex;
	int totalFrame;
	bool looped;
	Sprite* currentActiveSprite;
};

