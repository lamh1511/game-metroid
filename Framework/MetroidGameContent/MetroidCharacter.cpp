#include "MetroidCharacter.h"
#include "MetroidContent.h"
#include "Zoomer.h"
#include "SamusAnimation.h"
#include "Main\GameSystem.h"
#include "GameOverScreen.h"

MetroidCharacter::MetroidCharacter() :
	GameObject(Transform(), "Player", "Samus"),
	energy(36),
	rocketCount(2),
	energyTankCount(0),
	missileRocketEnabled(false),
	bombEnabled(false),
	longBeamEnabled(false)
{

	this->name = "Samus";
	this->isControllable = true;
	OnDamage = 0;
	canShoot = 1;
	OnDamageTime = 0;
	DisableInput = 0;
	shootDelayTime = 0;
	WeaponType = &SamusDamage::WaveBeam;
	this->OnDamageSprite = AddComponent<SpriteRenderer>();
	OnDamageSprite->SetDrawOrder(0);
	OnDamageSprite->SetSprite(MetroidContent::GetObjectByName<Sprite>("TileSet_0"));

	CharacterPhysics = AddComponent<SimulatePhysics>();
	CharacterPhysics->SetBodySize(SAMUSBODYSIZE);
	CharacterPhysics->SetMass(5.0f);
	CharacterPhysics->SetStatic(0);

	animation = AddComponent<SamusAnimation>();
}

MetroidCharacter::~MetroidCharacter()
{
}

void MetroidCharacter::Fire(const Vec2 & direction)
{
	if (shootDelayTime > 0 || (canShoot == 0 && WeaponType != &SamusDamage::SamusBomb)) return;

	if (WeaponType == &SamusDamage::WaveBeam)
	{
		shootDelayTime = SHOOTDELAYTIME_WAVEBEAM;
	}
	else
	{
		shootDelayTime = SHOOTDELAYTIME;
	}

	if (direction.x > 0)
	{
		GetScene()->SpawnNewGameObject(new SamusDamage(Vec2(transform.position.x + 0.1f, transform.position.y + 0.35f), direction, WeaponType));
	}
	else if (direction.x < 0)
	{
		GetScene()->SpawnNewGameObject(new SamusDamage(Vec2(transform.position.x - 0.1f, transform.position.y + 0.35f), direction, WeaponType));
	}
	else
	{
		GetScene()->SpawnNewGameObject(new SamusDamage(Vec2(transform.position.x, transform.position.y + 0.75f), direction, WeaponType));
	}
}

void MetroidCharacter::OnSpawn()
{
	GameObject::OnSpawn();
	camera = scene->FindGameObjectByName("MainCamera");
	OnDamageSprite->SetActive(0);
	//this->SetTransform(Transform(Vec2(38.0f, 79.5f)));
	moveSpeed = 6.0f;
	jumpSpeed = 12.0f;
	jumpTime = 0;
}

void MetroidCharacter::Update()
{
	if (Input::IsKeyPressed(VK_NUMPAD0))
	{
		this->WeaponType = &SamusDamage::NormalBeam;
	}
	else if (Input::IsKeyPressed(VK_NUMPAD1))
	{
		this->WeaponType = &SamusDamage::MissileRocket;
	}
	else if (Input::IsKeyPressed(VK_NUMPAD2))
	{
		this->WeaponType = &SamusDamage::IceBeam;
	}
	else if (Input::IsKeyPressed(VK_NUMPAD3))
	{
		this->WeaponType = &SamusDamage::WaveBeam;
	}
	else if (Input::IsKeyPressed(VK_NUMPAD4))
	{
		this->WeaponType = &SamusDamage::SamusBomb;
	}
	if (energy <= 0)
	{
		if (energyTankCount > 0)
		{
			energyTankCount -= 1;
			energy = 99;
			if (energyTankCount <= 0) energyTankCount = 0;
		}
		else energy = 0;
	}
	if (rocketCount <= 0) rocketCount = 0;
	if (energy == 0) scene->SpawnNewGameObject<GameOverScreen>(Transform(Vec2(camera->GetTransform().position)));

	GameSystem::SetText(std::to_string(energy), HP);
	GameSystem::SetText(std::to_string(rocketCount), ROCKET_COUNT);
	if (OnDamageTime <= 0 && Input::locked == 0)
	{
		CharacterPhysics->SetVelocityX(0);
		if (Input::IsKeyDown(VK_LEFT))
		{
			CharacterPhysics->SetVelocityX(-moveSpeed);
		}
		else if (Input::IsKeyDown(VK_RIGHT))
		{
			CharacterPhysics->SetVelocityX(moveSpeed);
		}
	}
	shootDelayTime -= Time::GetDeltaTime();
	GameObject::Update();

	if (Input::IsKeyDown(VK_X) && !Input::IsKeyDown(VK_UP))
	{
		Fire(Vec2(transform.scale.x, 0));
	}
	else if (Input::IsKeyPressed(VK_Z) && missileRocketEnabled && rocketCount > 0)
	{
		rocketCount -= 1;
		void (SamusDamage::*SamusWeaponType)();
		SamusWeaponType = WeaponType;
		WeaponType = &SamusDamage::MissileRocket;
		Fire(Vec2(transform.scale.x, 0));
		WeaponType = SamusWeaponType;
	}

	if (Input::IsKeyPressed(VK_C) && CharacterPhysics->GetVelocity().y == 0)
	{
		jumpTime = 0.45;
	}
	jumpTime -= Time::GetDeltaTime();
	if (Input::IsKeyReleased(VK_C) || jumpTime < 0)
	{
		jumpTime = 0;
	}
	if (jumpTime > 0)
	{
		CharacterPhysics->SetVelocityY(jumpSpeed);
	}

	if (OnDamage == 1)
	{
		OnDamage = 0;
		if (animation->currentAnimation != animation->roll && CharacterPhysics->GetVelocity().x != 0 && CharacterPhysics->GetVelocity().y == 0)
		{
			animation->currentAnimation = animation->idle;
			animation->LockCurrentState(1);
		}
	}

	if (OnDamageTime > 0) OnDamageTime -= Time::GetDeltaTime();
	if (OnDamageTime <= 0)
	{
		animation->color = ARGB(255, 255, 255, 255);
		animation->LockCurrentState(0);
	}
}

void MetroidCharacter::Teleport()
{
	if (Input::IsKeyPressed(VK_A))
	{
		transform.position = Vec2(69.44f, 265.28f);
		camera->SetTransform(Transform(Vec2(73.5f, 262.5f)));
	}
	else if (Input::IsKeyPressed(VK_S))
	{
		transform.position = Vec2(325.5f, 127.5f);
		camera->SetTransform(Transform(Vec2(325.5f, 127.5f)));
	}
}

void MetroidCharacter::OnCollisionEnter(GameObject * other, const Vec2& normal)
{
	if (other->GetComponent<SimulatePhysics>()->IsTrigger() == 0 && jumpTime > 0 && normal.y == 1.0f)// Kiem tra tren dau
	{
		jumpTime = 0;
		return;
	}
	if (other->GetTag() == "Enemy")
	{
		//
	}
}

void MetroidCharacter::LateUpdate()
{
	GameObject::LateUpdate();
	Teleport();
}
