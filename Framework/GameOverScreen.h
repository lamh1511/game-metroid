#pragma once
#include "GameFramework\GameObject\GameObject.h"
class GameOverScreen : public GameObject
{
public:
	GameOverScreen();
	virtual ~GameOverScreen();
	virtual void LateUpdate() override;
	virtual void OnSpawn() override;
	SpriteRenderer* sprite;
};

