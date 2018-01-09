#pragma once
#include "GameFramework\GameObject\GameObject.h"

class MetroidCharacter;

enum ITEM_TYPE
{
	MISSILE_ROCKET,
	ICE_BEAM,
	LONG_BEAM,
	VARIA,
	ENERGY_TANK,
	BOMB,
	WAVE_BEAM
};
class Items : public GameObject
{
public:
	Items(ITEM_TYPE type = MISSILE_ROCKET);
	virtual void OnSpawn() override;
	virtual void OnCollisionEnter(GameObject* other, const Vec2& normal = Vec2()) override;
	SimulatePhysics* physics;
	MetroidCharacter* Samus;
	virtual ~Items();

	void (Items::*UpdateSamus)();
	void EquipMissileRocket();
	void EquipIceBeam();
	void EquipLongBeam();
	void EquipVaria();
	void EquipBomb();
	void EquipWaveBeam();
	void EquipEnergyTank();
};

