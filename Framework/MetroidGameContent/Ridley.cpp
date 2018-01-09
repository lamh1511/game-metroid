#include "Ridley.h"
#include "MetroidContent.h"
#include "RidleyAnimation.h"
#include "GameFramework\GameComponent\CameraComponent.h"
#include "RidleyBullet.h"
#include "SamusAnimation.h"

SimulatePhysics* RidleyPhysics = nullptr;

Ridley::Ridley() :
	GameObject(Transform(), "Boss", "Ridley"),
	Damage(20)
{
	this->transform.position.y += 2.0f;
	this->name = "Ridley";

	physics = AddComponent<SimulatePhysics>();
	physics->SetBodySize(Vec2(1.0f, 2.5f));
	physics->SetStatic(false);
	physics->DisableCollision(true);
	physics->SetMass(0);

	animation = AddComponent<RidleyAnimation>();


	vx = 2.0f;
	vy = 4.0f;
	rotate = (int)GetTransform().rotation;
	flag = 0;
	countTime = 0;
	damagedTimer = 0;
	waiting = 0;
	maxH = 265.0f;

	hp = 5000;
	damaged = 0;
	damagedIdle = 0;
	damagedJump = 0;

	isDead = false;
	deadTimer = 0;
}


Ridley::~Ridley()
{
}

int Ridley::checkTopTile(Vec2 body) {
	int checkY = body.y;
	if (checkY > maxH)
		return 1;
	return 0;
}

int Ridley::checkDamaged(int isDamaged)
{
	if (isDamaged)
		return 1;
	return 0;
}

void Ridley::resetNoDamage()
{
	if (damaged)
	{
		damagedTimer += Time::GetDeltaTime();

		if (damagedTimer > 0.3)
		{
			damaged = 0;
			damagedIdle = 0;
			damagedJump = 0;
			damagedTimer = 0;
		}
	}
	else
		damagedTimer = 0;
}

int Ridley::checkSamusGun(int samusGun)
{
	if (samusGun == 0) // súng ko đóng băng
		return 0;
	else if (samusGun == 1) // súng đóng băng
		return 1;
}

void Ridley::OnCollisionEnter(GameObject * other, const Vec2 & normal)
{
	if (other->GetTag() == "SamusDamage")
	{
		hp -= static_cast<SamusDamage*>(other)->damage;
		if (hp <= 0) isDead = true;
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



void Ridley::moveState()
{
	if (0)//checkSamusGun(samus->gun)==0
	{
		float dt = (float)Time::GetDeltaTime();

		if (flag == 0)
		{
			if (checkDamaged(damaged))
				damagedJump = 1;

			ridley.y += vy * dt;
			countTime += dt;
			if (checkTopTile(ridley))
			{
				flag = 3;
				countTime = 0;
			}
		}

		if (flag == 1)
		{
			if (checkDamaged(damaged))
				damagedJump = 1;

			ridley.y -= vy * dt;
			countTime += dt;
			if (checkBottomTile(ridley))
			{
				flag = 2;
				countTime = 0;
				waiting = 1;
				// bắn đạn
				RidleyBullet* bb = GetScene()->SpawnNewGameObject<RidleyBullet>(Transform());
				bb->Fire(Vec2(GetTransform().position.x + 0.9f, GetTransform().position.y + 0.3f), Vec2(1.0f, 0));
			}
		}

		if (flag == 2)
		{
			if (checkDamaged(damaged))
				damagedIdle = 1;

			countTime += dt;
			if (countTime > 1.2)
			{
				waiting = 0;
				countTime = 0;
				flag = 0;
			}
		}

		if (flag == 3)
		{
			if (checkDamaged(damaged))
				damagedJump = 1;
			countTime += dt;

			if (countTime > 0.2)
			{
				countTime = 0;
				flag = 1;
			}
		}
	}
	else if (1)//checkSamusGun(samus->gun)==1
	{
		float dt = (float)Time::GetDeltaTime();

		if (flag == 0)
		{
			if (checkDamaged(damaged))
				damagedJump = 1;

			if (damaged)
				ridley.y += 2.0*dt;
			else
				ridley.y += vy * dt;

			countTime += dt;
			if (checkTopTile(ridley))
			{
				flag = 3;
				countTime = 0;
			}

		}

		if (flag == 1)
		{
			if (checkDamaged(damaged))
				damagedJump = 1;

			if (damaged)
				ridley.y -= 2.0*dt;
			else
				ridley.y -= vy * dt;

			countTime += dt;
			if (checkBottomTile(ridley))
			{
				flag = 2;
				countTime = 0;
				waiting = 1;

				if (!isDead)
				{
					// bắn đạn
					RidleyBullet* bb = GetScene()->SpawnNewGameObject<RidleyBullet>(Transform());
					bb->Fire(Vec2(GetTransform().position.x + 0.9f, GetTransform().position.y + 0.3f), Vec2(1.0f, 0));
				}

			}
		}

		if (flag == 2)
		{
			if (checkDamaged(damaged))
				damagedIdle = 1;

			countTime += dt;
			if (countTime > 1.2)
			{
				waiting = 0;
				countTime = 0;
				flag = 0;
			}
		}

		if (flag == 3)
		{
			if (checkDamaged(damaged))
				damagedJump = 1;
			countTime += dt;

			if (countTime > 0.2)
			{
				countTime = 0;
				flag = 1;
			}
		}
	}
}

int Ridley::checkBottomTile(Vec2 body) {
	int check = CameraComponent::tiles[(int)(body.y - 1.25f)][(int)body.x];
	if (check != -1)
		return 1;
	return 0;
}

void Ridley::OnSpawn()
{
	GameObject::OnSpawn();
	//animation->SetActive(0);
	transform.position.y = 263.5f;
	ridley = GetTransform().position;
	Samus = static_cast<MetroidCharacter*>(this->GetScene()->FindGameObjectByName("Samus"));
}

void Ridley::Update()
{
	GameObject::Update();

	if (isDead)
		deadTimer += Time::GetDeltaTime();

	if (deadTimer >= 2.1 && isDead)
	{
		GetScene()->DestroyGameObject(this);
	}

	moveState();

	resetNoDamage();

	SetTransform(Transform(Vec2(ridley.x, ridley.y), 0));

}
