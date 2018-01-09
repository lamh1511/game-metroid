#include "Animation.h"
#include "GameFramework\Time.h"


Animation::Animation()
{
}


Animation::Animation(std::vector<Sprite*> sprites, double timePerFrame, bool looped, const std::string& name):
	Object(name),
	sprites(sprites),
	timePerFrame(timePerFrame),
	looped(looped),
	currentIndex(0),
	currentTotalTime(0),
	totalFrame((int)sprites.size())
{
	currentActiveSprite = sprites.at(0);
}

Animation::~Animation()
{
}

bool Animation::PlayBack()
{
	if (!currentActiveSprite) return 1;
	if (totalFrame <= 1)
	{
		if(looped) currentActiveSprite = sprites.at(0);
		else
		{
			currentActiveSprite = nullptr;
		}
		return 1;
	}
	else
	{
		if (currentTotalTime >= timePerFrame)
		{
			currentTotalTime = 0;
			currentIndex++;
			if (currentIndex >= totalFrame)
			{
				if (looped)
				{
					currentIndex = 0;
					currentActiveSprite = sprites.at(currentIndex);
					return 1;
				}
				else
				{
					currentActiveSprite = nullptr;
					return 1;
				}
			}
		}
		else
		{
			currentTotalTime += Time::GetDeltaTime();
		}
		currentActiveSprite = sprites.at(currentIndex);
	}
	return 0;
}

void Animation::Reset()
{
	currentIndex = 0;
	currentTotalTime = 0;
	currentActiveSprite = sprites.at(currentIndex);
}

Sprite * Animation::GetActiveSprite()
{
	return currentActiveSprite;
}
