#include "PortalEntrance.h"
#include "Portal.h"
#include "MetroidContent.h"
#include "Bomb.h"

PortalEntrance::PortalEntrance(bool isRedPortal):
	isRedPortal(isRedPortal)
{
	this->tag = "PortalEntrance";
	this->isAlwaysActive = false; // portal se update class nay
	physics = AddComponent<SimulatePhysics>();
	physics->SetBodySize(Vec2(1.0f, 3.0f));
	physics->SetStatic(false);
	physics->DisableCollision(false);
	physics->SetMass(0);
	openTime = 0;

	animation = AddComponent<AnimationController>();
	if (isRedPortal)
	{
		open = animation->AddAnimation(MetroidContent::GetObjectByName<Animation>("OpenRedPortal"));
		close = animation->AddAnimation(MetroidContent::GetObjectByName<Animation>("CloseRedPortal"));
		normal = animation->AddAnimation(MetroidContent::GetObjectByName<Animation>("NormalRedPortalEntrance"));
	}
	else
	{
		open = animation->AddAnimation(MetroidContent::GetObjectByName<Animation>("OpenPortal"));
		close = animation->AddAnimation(MetroidContent::GetObjectByName<Animation>("ClosePortal"));
		normal = animation->AddAnimation(MetroidContent::GetObjectByName<Animation>("NormalPortalEntrance"));
	}
	
	animation->currentAnimation = normal;

}


PortalEntrance::~PortalEntrance()
{
}

void PortalEntrance::OnCollisionEnter(GameObject * other, const Vec2 & normal)
{
	if (other->GetTag() == "SamusDamage")
	{
		if (isRedPortal)
		{
			if (animation->currentAnimation == this->normal && other->GetName() == "MissileRocket")
			{
				animation->currentAnimation = open;
			}
		}
		else if (animation->currentAnimation == this->normal)
		{
			animation->currentAnimation = open;
		}

	}
	if (other->GetTag() == "Bomb")
	{
		if (static_cast<Bomb*>(other)->UpdateState == &Bomb::Explode)
		{
			animation->currentAnimation = open;
		}
	}
}

void PortalEntrance::Update()
{
	GameObject::Update();
	if (animation->currentAnimation == open)
	{
		physics->DisableCollision(true);
		openTime += Time::GetDeltaTime();
		if (openTime >= 2.0)
		{
			animation->currentAnimation->Reset();
			animation->currentAnimation = close;
			openTime = 0;
		}
	}
	else
	{
		physics->DisableCollision(false);
	}
	if (animation->currentAnimation == close && animation->currentAnimation->GetActiveSprite() == nullptr)
	{
		animation->currentAnimation->Reset();
		animation->currentAnimation = normal;
	}
}
