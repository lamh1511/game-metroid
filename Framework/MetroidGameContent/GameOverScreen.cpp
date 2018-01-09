#include "GameOverScreen.h"
#include "MetroidContent.h"
#include "Main\GameSystem.h"

GameOverScreen::GameOverScreen()
{
	sprite = AddComponent<SpriteRenderer>();
	sprite->SetSprite(MetroidContent::GetObjectByName<Sprite>("Menus_0"));
	sprite->SetDrawOrder(200);

}


GameOverScreen::~GameOverScreen()
{
}

void GameOverScreen::LateUpdate()
{
	GameSystem::SetTextVisibility(0);
	GameObject::LateUpdate();
	scene->DestroyGameObject(this);
	PostQuitMessage(0);
}

void GameOverScreen::OnSpawn()
{
	GameObject::OnSpawn();
}
