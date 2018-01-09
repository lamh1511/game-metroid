#pragma once
#include "GameFramework\GameObject\GameObject.h"


class Spawner : public GameObject
{
public:
	Spawner();
	virtual ~Spawner();
	GameObject* gameObject;
	SimulatePhysics* gameObjectPhysic;
	bool canBeUpdated;

	virtual void OnSpawn() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

	void SetSpawnType(const std::string& Type);
	void (Spawner::*SpawnGameObject)();
	void SpawnZoomer();
	void SpawnSkree();
	void SpawnRio();
	void SpawnItem();

	GameObject* GetGameObject();
	void DestroyGameObject();
};

