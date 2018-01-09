#include "Kraid.h"
#include "MetroidContent.h"
#include "KraidAnimation.h"
#include "GameFramework\GameComponent\CameraComponent.h"
#include "KraidBullet.h"
#include "SamusAnimation.h"
#include "Bumerang.h"

SimulatePhysics* KraidPhysics = nullptr;

Kraid::Kraid() :
	GameObject(Transform(), "Boss", "Kraid")
{
	Damage = 15;
	physics = AddComponent<SimulatePhysics>();
	physics->SetBodySize(Vec2(1.0f, 2.5f));
	physics->SetStatic(false);
	physics->DisableCollision(true);
	physics->SetMass(0);

	AddComponent<KraidAnimation>();

	vx = 1.5f;
	vy = 4.0f;
	rotate = (int)GetTransform().rotation;
	direction = 1.0f;
	flag = 0;
	countTime = 0;
	damagedTimer = 0;
	waiting = 0;

	hp = 5000;
	damaged = 0;

	fireTimer = 0;
}


Kraid::~Kraid()
{
}

int Kraid::checkDamaged(int isDamaged)
{
	if (isDamaged)
		return 1;
	return 0;
}

void Kraid::resetNoDamage()
{
	if (damaged)
	{
		damagedTimer += Time::GetDeltaTime();

		if (damagedTimer > 0.3)
		{
			damaged = 0;
			damagedTimer = 0;
		}
	}
	else
		damagedTimer = 0;
}

int Kraid::checkSamusGun(int samusGun)
{
	if (samusGun == 0) // súng ko đóng băng
		return 0;
	else if (samusGun == 1) // súng đóng băng
		return 1;
}

void Kraid::setDirection(Vec2 samusPosition)
{
	if (samusPosition.x > kraid.x)
		direction = 1.0f; // right
	else
		direction = -1.0f; // left
}

void Kraid::OnCollisionEnter(GameObject * other, const Vec2 & normal)
{
	if (other->GetTag() == "SamusDamage")
	{
		hp -= static_cast<SamusDamage*>(other)->damage;
		damaged = 1;
	}
	else if (other->GetTag() == "Player")
	{
		if (Samus->OnDamageTime <= 0)
		{
			Samus->energy -= this->Damage;
			Samus->OnDamage = 1;
			Samus->jumpTime = 0;
			Samus->OnDamageTime = 0.2;
			Samus->animation->color = ARGB(100, 255, 255, 255);
			if (CameraComponent::tiles[(int)(Samus->GetTransform().position.y - 1.5f)][(int)Samus->GetTransform().position.x] == -1)
			{
				Samus->CharacterPhysics->SetVelocityY(0.0f);
			}
			else
			{
				if (normal.x == 1.0f)
				{
					Samus->CharacterPhysics->SetVelocityX(7.0f);
				}
				else
				{
					Samus->CharacterPhysics->SetVelocityX(-7.0f);
				}
			}
		}

	}
}

void Kraid::moveState()
{
	float dt = (float)Time::GetDeltaTime();

	setDirection(Samus->GetTransform().position);

	if (flag == 0)
	{
		countTime += dt;
		kraid.x += vx * dt;
		if (countTime > 2.0)
		{
			countTime = 0;
			flag = 1;
		}
	}

	if (flag == 1)
	{
		countTime += dt;
		kraid.x -= vx * dt;

		fireTimer += dt;

		if (countTime > 2.0)
		{
			countTime = 0;
			flag = 0;
			// bắn đạn
			KraidBullet* bb = GetScene()->SpawnNewGameObject<KraidBullet>(Transform());
			bb->Fire(Vec2(0.7f, 0.0f), direction);

			KraidBullet* bb1 = GetScene()->SpawnNewGameObject<KraidBullet>(Transform());
			bb1->Fire(Vec2(0.6f, 0.4f), direction);

			KraidBullet* bb2 = GetScene()->SpawnNewGameObject<KraidBullet>(Transform());
			bb2->Fire(Vec2(0.8f, -0.4f), direction);

			Bumerang* bmr = GetScene()->SpawnNewGameObject<Bumerang>(Transform());
			bmr->Fire(Vec2(GetTransform().position.x + 0.9f, GetTransform().position.y + 0.3f), direction);
		}

		if (fireTimer > 2.3)
		{
			fireTimer = 0;

			Bumerang* bmr1 = GetScene()->SpawnNewGameObject<Bumerang>(Transform());
			bmr1->Fire(Vec2(GetTransform().position.x + 0.9f, GetTransform().position.y + 0.3f), direction);
		}
	}
}

void Kraid::OnSpawn()
{
	GameObject::OnSpawn();

	kraid = GetTransform().position;

	Samus = static_cast<MetroidCharacter*>(GetScene()->FindGameObjectByName("Samus"));
}

void Kraid::Update()
{
	GameObject::Update();

	moveState();
	if (hp <= 0)scene->DestroyGameObject(this);
	SetTransform(Transform(Vec2(kraid.x, kraid.y), 0, Vec2(direction, 1.0f)));
}
