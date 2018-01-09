#include "Enemy.h"
#include "MetroidCharacter.h"
#include "SamusAnimation.h"
#include "EnergyBall.h"
#include "Explosion.h"

Enemy::Enemy() :
	GameObject(Transform(), "Enemy", "EnemyClass"),
	isFrozen(0),
	OnGetDamageDelayTime(0),
	freezeTime(0),
	Health(20),
	Damage(5),
	animation(nullptr),
	physics(nullptr)
{
}

void Enemy::OnSpawn() {
	GameObject::OnSpawn();
	position = transform.position;
	Samus = static_cast<MetroidCharacter*>(GetScene()->FindGameObjectByName("Samus"));
	//speedX = vx;
	//speedY = vy;
}

void Enemy::OnCollisionEnter(GameObject * other, const Vec2 & normal)
{
	if (other->GetName() != "Bomb")
	{
		animation->Pause(1);
		OnGetDamageDelayTime = 0.3;
	}

	if (other->GetTag() == "Player" && isFrozen == 0)
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

void Enemy::Update() {
	GameObject::Update();
	if (Health <= 0) GetScene()->DestroyGameObject(this);
	OnGetDamageDelayTime -= Time::GetDeltaTime();
	if (OnGetDamageDelayTime <= 0 && isFrozen == 0)
	{
		animation->Pause(0);
		//vx = speedX;
		//vy = speedY;
	}
	if (isFrozen == 1)
	{
		if (freezeTime > 0) freezeTime -= Time::GetDeltaTime();
		if (freezeTime <= 0)
		{
			animation->SetColor(ARGB(255, 255, 255, 255));
			animation->Pause(0);
			//vx = speedX;
			//vy = speedY;
			tag = "Enemy";
			physics->DisableCollision(1);
			physics->SetStatic(0);
			isFrozen = 0;
		}
	}

	if (Health <= 0)
	{
		if (2 == Random_Int(1, 3))
		{
			scene->SpawnNewGameObject<EnergyBall>(Transform(transform.position));
		}
		scene->SpawnNewGameObject<Explosion>(Transform(transform.position));
		scene->DestroyGameObject(this);
	}

}

void Enemy::Freeze()
{
	animation->SetColor(ARGB(255, 0, 65, 255));
	animation->Pause(1);
	//vx = 0;
	//vy = 0;
	physics->SetVelocity(Vec2(0, 0));
	this->tag = "Enemy";
	physics->DisableCollision(0);
	physics->SetStatic(1);
	freezeTime = 5.0;
	isFrozen = 1;
}


int Enemy::CheckTopTile(Vec2& position) {
	int i = CameraComponent::tiles[(int)(position.y + 0.5f)][(int)(position.x)];
	if (i == -1 || i == 40 || i == 36 || i == 37 || i == 320 || i == 321) {
		return 0;
	}
	else
	{
		position.y = (int)(position.y + 0.5f) - 0.5f;
		return 1;
	}
}

int Enemy::CheckBottomTile(Vec2& position) {
	int i = CameraComponent::tiles[(int)(position.y - 0.5f)][(int)(position.x)];
	if (i == -1 || i == 40 || i == 36 || i == 37 || i == 320 || i == 321)
	{
		return 0;
	}
	else
	{
		position.y = (int)(position.y - 0.5f) + 1.5f;
		return 1;
	}
}

int Enemy::CheckLeftTile(Vec2& position) {
	int i = CameraComponent::tiles[(int)(position.y)][(int)(position.x - 0.5f)];
	if (i == -1 || i == 40 || i == 36 || i == 37 || i == 320 || i == 321)
	{
		return 0;
	}
	else
	{
		position.x = (int)(position.x - 0.5f) + 1.5f;
		return 1;
	}
}

int Enemy::CheckRightTile(Vec2& position) {
	int i = CameraComponent::tiles[(int)(position.y)][(int)(position.x + 0.5f)];
	if (i == -1 || i == 40 || i == 36 || i == 37 || i == 320 || i == 321)
	{
		return 0;
	}
	else
	{
		position.x = (int)(position.x + 0.5f) - 0.5f;
		return 1;
	}
}