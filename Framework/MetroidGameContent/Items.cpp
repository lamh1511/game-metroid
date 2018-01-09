#include "Items.h"
#include "SamusAnimation.h"
#include "MetroidCharacter.h"
#include "MetroidContent.h"

Items::Items(ITEM_TYPE type)
{
	AnimationController* animation = AddComponent<AnimationController>();
	if (type == MISSILE_ROCKET)
	{
		UpdateSamus = &Items::EquipMissileRocket;
		animation->AddMainAnimation(MetroidContent::GetObjectByName<Animation>("MissileRocketAnimation"));
	}
	else if (type == ICE_BEAM)
	{
		UpdateSamus = &Items::EquipIceBeam;
		animation->AddMainAnimation(MetroidContent::GetObjectByName<Animation>("IceBeamAnimation"));
	}

	else if (type == VARIA)
	{
		UpdateSamus = &Items::EquipVaria;
		animation->AddMainAnimation(MetroidContent::GetObjectByName<Animation>("VariaAnimation"));
	}
	else if (type == ENERGY_TANK)
	{
		UpdateSamus = &Items::EquipEnergyTank;
		animation->AddMainAnimation(MetroidContent::GetObjectByName<Animation>("EnergyTankAnimation"));
	}
	else if (type == BOMB)
	{
		UpdateSamus = &Items::EquipBomb;
		animation->AddMainAnimation(MetroidContent::GetObjectByName<Animation>("BombAnimation"));
	}
	else if (type == WAVE_BEAM)
	{
		UpdateSamus = &Items::EquipWaveBeam;
		animation->AddMainAnimation(MetroidContent::GetObjectByName<Animation>("WaveBeamAnimation"));
	}
	else if (type == LONG_BEAM)
	{
		UpdateSamus = &Items::EquipLongBeam;
		animation->AddMainAnimation(MetroidContent::GetObjectByName<Animation>("LongBeamAnimation"));
	}
	physics = AddComponent<SimulatePhysics>();
	physics->SetBodySize(Vec2(1.0f, 1.0f));
	physics->SetStatic(true);
	physics->SetVelocity(Vec2(0, 0));
	physics->DisableCollision(true);
	physics->SetMass(0);
}

void Items::OnSpawn()
{
	GameObject::OnSpawn();
	Samus = static_cast<MetroidCharacter*>(GetScene()->FindGameObjectByName("Samus"));
}

void Items::OnCollisionEnter(GameObject * other, const Vec2 & normal)
{
	if (other == Samus)
	{
		scene->DestroyGameObject(this);
		(*this.*UpdateSamus)();
		Sleep(3000);
	}
}


Items::~Items()
{
}

void Items::EquipMissileRocket()
{
	Samus->missileRocketEnabled = true;
	Samus->rocketCount += 100;
}

void Items::EquipIceBeam()
{
	Samus->WeaponType = &SamusDamage::IceBeam;
}

void Items::EquipLongBeam()
{
	Samus->longBeamEnabled = true;
}

void Items::EquipVaria()
{

}

void Items::EquipBomb()
{
	Samus->bombEnabled = true;
}

void Items::EquipWaveBeam()
{
	Samus->WeaponType = &SamusDamage::WaveBeam;
}

void Items::EquipEnergyTank()
{
	Samus->energyTankCount += 1;
}
