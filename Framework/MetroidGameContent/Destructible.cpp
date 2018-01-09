#include "Destructible.h"
#include "Bomb.h"


Destructible::Destructible() :
	relive(0)
{
	this->tag = "Destructible";
	UpdateState = &Destructible::VoidFunc;

	physics = AddComponent<SimulatePhysics>();
	physics->SetBodySize(Vec2(1.0f, 1.0f));
	physics->SetStatic(false);
	physics->DisableCollision(false);
	physics->SetMass(0);
}


Destructible::~Destructible()
{
}

void Destructible::CountDown()
{
	relive -= Time::GetDeltaTime();
	if (relive <= 0)
	{
		UpdateState = &Destructible::VoidFunc;
		physics->SetBodySize(Vec2(1.0f, 1.0f));
		physics->DisableCollision(false);
		CameraComponent::tiles[(int)(transform.position.y)][(int)transform.position.x] = this->idBlock;
	}
}

void Destructible::VoidFunc()
{
}

void Destructible::DestroySelf()
{
	CameraComponent::tiles[(int)(transform.position.y)][(int)transform.position.x] = -1;
	UpdateState = &Destructible::CountDown;
	physics->DisableCollision(true);
	physics->SetBodySize(Vec2(0, 0));
	relive = RELIVE_TIME;
}

void Destructible::OnSpawn()
{
	GameObject::OnSpawn();
	this->idBlock = CameraComponent::tiles[(int)transform.position.y][(int)transform.position.x];
	std::cout << idBlock;
}

void Destructible::Update()
{
	GameObject::Update();
	(*this.*UpdateState)();
}

void Destructible::OnCollisionEnter(GameObject * other, const Vec2 & normal)
{

	if (other->GetTag() == "SamusDamage")
	{
		DestroySelf();
	}
	else if (other->GetTag() == "Bomb")
	{
		if (static_cast<Bomb*>(other)->UpdateState == &Bomb::Explode)
		{
			DestroySelf();
		}
	}
}

