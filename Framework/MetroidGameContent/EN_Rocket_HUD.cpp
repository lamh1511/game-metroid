#include "EN_Rocket_HUD.h"
#include "MetroidContent.h"
#include "MainCamera.h"

EN_Rocket_HUD::EN_Rocket_HUD()
{
	sprite = AddComponent<SpriteRenderer>();
	sprite->SetDrawOrder(100);
	sprite->SetSprite(MetroidContent::GetObjectByName<Sprite>("TileSet_80"));
}


EN_Rocket_HUD::~EN_Rocket_HUD()
{
}

void EN_Rocket_HUD::OnSpawn()
{
	GameObject::OnSpawn();
	mainCamera = scene->FindGameObjectByName("MainCamera");
}

void EN_Rocket_HUD::LateUpdate()
{
	transform.position = mainCamera->GetTransform().position + Vec2(-5.5f, 4.0f);
	GameObject::LateUpdate();
}
