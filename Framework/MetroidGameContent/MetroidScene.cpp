#include "MetroidScene.h"
#include "MetroidContent.h"
#include "MetroidCharacter.h"
#include "MainCamera.h"
#include "QuadTree.h"
#include "Portal.h"
#include "PortalEntrance.h"
#include "Ripper.h"
#include "Rio.h"
#include "Zeb.h"
#include "Waver.h"
#include "Kraid.h"
#include "Ridley.h"
#include "Bomb.h"
#include "EN_Rocket_HUD.h"
#include "Items.h"

MetroidScene::MetroidScene(const std::string & name) :
	Scene(name)
{
	/*GameObject* brinstar = new GameObject(Transform(Vec2(240.1563f, 142.6563f)), "Brinstar", "Brinstar", 1);
	SpriteRenderer* s = brinstar->AddComponent<SpriteRenderer>();
	s->SetSprite(MetroidContent::GetObjectByName<Sprite>("Brinstar"));
	s->SetDrawOrder(2);
	SpawnNewGameObject(brinstar);*/
	//-----------------------------------------------------------
	this->MetroidQuadtree = QuadTree::BuildQuadtreeFromFile("MetroidLevel.xml", this);
	//-----------------------------------------------------------
	SpawnNewGameObject<MetroidCharacter>(Transform(Vec2(38.0f, 79.5f)));
	SpawnNewGameObject<MainCamera>(Transform(Vec2(38.0f, 82.5f)));
	/*Items* i = new Items(LONG_BEAM);
	i->SetTransform(Transform(Vec2(50.0f, 80.0f)));
	SpawnNewGameObject(i);*/
	SpawnNewGameObject<EN_Rocket_HUD>(Transform());
}

MetroidScene::~MetroidScene()
{
}
