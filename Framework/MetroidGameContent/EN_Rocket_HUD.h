#pragma once
#include "GameFramework\GameObject\GameObject.h"
class EN_Rocket_HUD : public GameObject
	
{
public:
	EN_Rocket_HUD();
	virtual ~EN_Rocket_HUD();
	SpriteRenderer* sprite;
	GameObject* mainCamera;
	virtual void OnSpawn() override;
	virtual void LateUpdate() override;
};

