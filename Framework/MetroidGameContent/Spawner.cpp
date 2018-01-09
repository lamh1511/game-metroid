#include "Spawner.h"
#include "GameFramework\Scene\Scene.h"
#include "Zoomer.h"
#include "Skree.h"
#include "Rio.h"
#include "MaruMari.h"
#include "Zeb.h"
#include "Ripper.h"
#include "Waver.h"
#include "Portal.h"
#include "Destructible.h"
#include "Items.h"
#include "Kraid.h"
#include "Ridley.h"

Spawner::Spawner() :
	GameObject(Transform(), "Spawner", "Spawner")
{
	SpawnGameObject = nullptr;
	gameObjectPhysic = nullptr;
	gameObject = nullptr;
	canBeUpdated = 1;
}


Spawner::~Spawner()
{
}

void Spawner::OnSpawn()
{
	GameObject::OnSpawn();
	GetScene()->SpawnNewGameObject(gameObject);
	gameObject->SetTransform(this->GetTransform());
}

void Spawner::Update()
{
	/*if (!gameObject) return;
	if (gameObjectPhysic->IsColliding(gameObjectPhysic->GetBodyRect(), GetScene()->camera->GetCameraRect())) canBeUpdated = 1;
	else canBeUpdated = 0;
	if (canBeUpdated == 1)
	{
		scene->GetCollisionBoxes().push_back(gameObjectPhysic);
		gameObject->Update();

	}*/
}

void Spawner::LateUpdate()
{
	/*if (!gameObject) return;
	if (canBeUpdated == 1) gameObject->LateUpdate();*/
}

void Spawner::SetSpawnType(const std::string & Type)
{
	if (Type == "Zoomer")
	{
		SpawnGameObject = &Spawner::SpawnZoomer;
		gameObject = new Zoomer();
		gameObjectPhysic = gameObject->GetComponent<SimulatePhysics>();
	}
	else if (Type == "Rio")
	{
		SpawnGameObject = &Spawner::SpawnRio;
		gameObject = new Rio();
		gameObjectPhysic = gameObject->GetComponent<SimulatePhysics>();
	}
	else if (Type == "Skree")
	{
		SpawnGameObject = &Spawner::SpawnSkree;
		gameObject = new Skree();
		gameObjectPhysic = gameObject->GetComponent<SimulatePhysics>();
	}
	else if (Type == "MaruMari")
	{
		SpawnGameObject = &Spawner::SpawnItem;
		gameObject = new MaruMari();
		gameObjectPhysic = gameObject->GetComponent<SimulatePhysics>();
	}
	else if (Type == "Zeb")
	{
		SpawnGameObject = &Spawner::SpawnItem;
		gameObject = new Zeb();
		gameObjectPhysic = gameObject->GetComponent<SimulatePhysics>();
	}
	else if (Type == "Ripper")
	{
		SpawnGameObject = &Spawner::SpawnItem;
		gameObject = new Ripper();
		gameObjectPhysic = gameObject->GetComponent<SimulatePhysics>();
	}
	else if (Type == "Waver")
	{
		SpawnGameObject = &Spawner::SpawnItem;
		gameObject = new Waver();
		gameObjectPhysic = gameObject->GetComponent<SimulatePhysics>();
	}
	else if (Type == "RedPortal")
	{
		SpawnGameObject = &Spawner::SpawnItem;
		gameObject = new Portal(1);
		gameObjectPhysic = gameObject->GetComponent<SimulatePhysics>();
	}
	else if (Type == "VHPortal")
	{
		SpawnGameObject = &Spawner::SpawnItem;
		gameObject = new Portal(0, MOVE_ALONG_Y_AXIS, MOVE_ALONG_X_AXIS);
		gameObjectPhysic = gameObject->GetComponent<SimulatePhysics>();
	}
	else if (Type == "HVPortal")
	{
		SpawnGameObject = &Spawner::SpawnItem;
		gameObject = new Portal(0, MOVE_ALONG_X_AXIS, MOVE_ALONG_Y_AXIS);
		gameObjectPhysic = gameObject->GetComponent<SimulatePhysics>();
	}
	else if (Type == "HHPortal")
	{
		SpawnGameObject = &Spawner::SpawnItem;
		gameObject = new Portal(0);
		gameObjectPhysic = gameObject->GetComponent<SimulatePhysics>();
	}
	else if (Type == "Block")
	{
		SpawnGameObject = &Spawner::SpawnItem;
		gameObject = new Destructible();
		gameObjectPhysic = gameObject->GetComponent<SimulatePhysics>();
	}
	else if (Type == "MissileRocket")
	{
		SpawnGameObject = &Spawner::SpawnItem;
		gameObject = new Items(MISSILE_ROCKET);
		gameObjectPhysic = gameObject->GetComponent<SimulatePhysics>();
	}
	else if (Type == "IceBeam")
	{
		SpawnGameObject = &Spawner::SpawnItem;
		gameObject = new Items(ICE_BEAM);
		gameObjectPhysic = gameObject->GetComponent<SimulatePhysics>();
	}
	else if (Type == "EnergyTank")
	{
		SpawnGameObject = &Spawner::SpawnItem;
		gameObject = new Items(ENERGY_TANK);
		gameObjectPhysic = gameObject->GetComponent<SimulatePhysics>();
	}
	else if (Type == "LongBeam")
	{
		SpawnGameObject = &Spawner::SpawnItem;
		gameObject = new Items(LONG_BEAM);
		gameObjectPhysic = gameObject->GetComponent<SimulatePhysics>();
	}
	else if (Type == "Bomb")
	{
		SpawnGameObject = &Spawner::SpawnItem;
		gameObject = new Items(BOMB);
		gameObjectPhysic = gameObject->GetComponent<SimulatePhysics>();
	}
	else if (Type == "Varia")
	{
		SpawnGameObject = &Spawner::SpawnItem;
		gameObject = new Items(VARIA);
		gameObjectPhysic = gameObject->GetComponent<SimulatePhysics>();
	}
	else if (Type == "WaveBeam")
	{
		SpawnGameObject = &Spawner::SpawnItem;
		gameObject = new Items(WAVE_BEAM);
		gameObjectPhysic = gameObject->GetComponent<SimulatePhysics>();
	}
	else if (Type == "Kraid")
	{
		SpawnGameObject = &Spawner::SpawnItem;
		gameObject = new Kraid();
		gameObjectPhysic = gameObject->GetComponent<SimulatePhysics>();
	}
	else if (Type == "Ridley")
	{
		SpawnGameObject = &Spawner::SpawnItem;
		gameObject = new Ridley();
		gameObjectPhysic = gameObject->GetComponent<SimulatePhysics>();
	}
	//--------------------------------------------------------------
	if (gameObject)
	{
		gameObject->spawner = this;
		gameObject->isAlwaysActive = false;
	}
}

void Spawner::SpawnZoomer()
{
	GetScene()->SpawnNewGameObject(gameObject);
}

void Spawner::SpawnSkree()
{
	GetScene()->SpawnNewGameObject(gameObject);
}

void Spawner::SpawnRio()
{
	GetScene()->SpawnNewGameObject(gameObject);
}

void Spawner::SpawnItem()
{
}

GameObject * Spawner::GetGameObject()
{
	if (gameObject)
	{
		if (gameObjectPhysic->IsColliding(gameObjectPhysic->GetBodyRect(), GetScene()->camera->GetCameraRect()))
		{
			return this->gameObject;
		}
		else return nullptr;
	}
	return nullptr;
}

void Spawner::DestroyGameObject()
{
	this->gameObject = nullptr;
	this->gameObjectPhysic = nullptr;
}
