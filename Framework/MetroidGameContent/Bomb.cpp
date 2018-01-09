#include "Bomb.h"
#include "Explosion.h"
#include "MetroidContent.h"
#include "Enemy.h"
#include "SamusAnimation.h"
#include "MetroidCharacter.h"
#include "Destructible.h"

Bomb::Bomb()
{
	tag = "Bomb";
	name = "Bomb";
	explosionTime = 0.1;
	damage = 10;
	this->lifeTime = 3.0;
	this->isControllable = true;
	UpdateState = &Bomb::CountDown;

	physics = AddComponent<SimulatePhysics>();
	physics->SetBodySize(Vec2(3.0f, 3.0f));
	physics->SetStatic(false);
	physics->DisableCollision(true);
	physics->SetMass(0);

	animation = AddComponent<AnimationController>();
	animation->sortingOrder = 1;
	animation->AddMainAnimation(MetroidContent::GetObjectByName<Animation>("SamusBombAnimation"));
}


Bomb::~Bomb()
{
}

void Bomb::Update()
{
	GameObject::Update();
	(*this.*UpdateState)();
}

void Bomb::OnSpawn()
{
	GameObject::OnSpawn();
	Samus = static_cast<MetroidCharacter*>(GetScene()->FindGameObjectByName("Samus"));
}

void Bomb::DestroyBlock()
{
	/*if (CameraComponent::tiles[(int)(transform.position.y) - 1][(int)transform.position.x] == 7 || CameraComponent::tiles[(int)(transform.position.y) - 1][(int)transform.position.x] == 46)
		CameraComponent::tiles[(int)(transform.position.y) - 1][(int)transform.position.x] = -1;

	if (CameraComponent::tiles[(int)(transform.position.y)][(int)transform.position.x + 1] == 7 || CameraComponent::tiles[(int)(transform.position.y) - 1][(int)transform.position.x] == 46)
		CameraComponent::tiles[(int)(transform.position.y)][(int)transform.position.x + 1] = -1;

	if (CameraComponent::tiles[(int)(transform.position.y)][(int)transform.position.x - 1] == 7 || CameraComponent::tiles[(int)(transform.position.y) - 1][(int)transform.position.x] == 46)
		CameraComponent::tiles[(int)(transform.position.y)][(int)transform.position.x - 1] = -1;

	if (CameraComponent::tiles[(int)(transform.position.y) + 1][(int)transform.position.x] == 7 || CameraComponent::tiles[(int)(transform.position.y) - 1][(int)transform.position.x] == 46)
		CameraComponent::tiles[(int)(transform.position.y) + 1][(int)transform.position.x] = -1;*/
}

void Bomb::CountDown()
{
	lifeTime -= Time::GetDeltaTime();
	if (lifeTime <= 0)
	{
		scene->SpawnNewGameObject<Explosion>(Transform(transform.position));
		animation->SetActive(0);
		UpdateState = &Bomb::Explode;
	}
}

void Bomb::Explode()
{
	explosionTime -= Time::GetDeltaTime();
	if (explosionTime <= 0)
	{
		scene->DestroyGameObject(this);
	}
	
	DestroyBlock();
	if (SimulatePhysics::IsColliding(physics->GetBodyRect(), Samus->CharacterPhysics->GetBodyRect()))
	{
		scene->DestroyGameObject(this);
		Samus->OnDamage = 1;
		Samus->jumpTime = 0;
		Samus->OnDamageTime = 0.3;
		Samus->animation->color = ARGB(100, 255, 255, 255);

		Vec2 forceDir = Samus->GetTransform().position - transform.position;
		if (std::abs(forceDir.x) < 0.4f)
		{
			Samus->CharacterPhysics->SetVelocity(Vec2(0, 23.0f));
		}
		else if(forceDir.x < 0)
		{
			Samus->CharacterPhysics->SetVelocity(Vec2(-20.0f, 0));
		}
		else
		{
			Samus->CharacterPhysics->SetVelocity(Vec2(20.0f, 0));
		}
	}
}

void Bomb::OnCollisionEnter(GameObject * other, const Vec2 & normal)
{
	if (UpdateState == &Bomb::Explode)
	{
		if (other->GetTag() == "Enemy")
		{
			Enemy* enemy = static_cast<Enemy*>(other);
			if (enemy->Health > 0)
			{
				enemy->Health -= damage;
			}
			scene->DestroyGameObject(this);
		}
	}
}

