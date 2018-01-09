#include "RidleyBullet.h"
#include "MetroidContent.h"
#include "RidleyBulletAnimation.h"
#include "GameFramework\GameComponent\CameraComponent.h"

RidleyBullet::RidleyBullet() :
	lifeTime(9),
	speedX(1.5f), speedY(8.0f)//8.0f //1.5f
{
	this->name = "RidleyBullet";
	Damage = 8;
	Health = 20;

	animation = AddComponent<AnimationController>();
	animation->AddMainAnimation(MetroidContent::GetObjectByName<Animation>("RidleyBulletAnimation"));

	physics = AddComponent<SimulatePhysics>();
	physics->SetBodySize(Vec2(0.2f, 0.2f));
	physics->SetStatic(false);
	physics->DisableCollision(true);
	physics->SetMass(0);

	AddComponent<RidleyBulletAnimation>(); //*

	x = 0;
	y = 0;
	//yMax = 82.5;
	A = 60;//60;
}


RidleyBullet::~RidleyBullet()
{
}

void RidleyBullet::Fire(const Vec2 & firePosition, const Vec2 & direction)
{
	this->SetTransform(Transform(firePosition));
	if (direction.GetNormalized() == Vec2(1.0f, 0))
	{
		this->GetTransform().scale = Vec2(1.0f, 1.0f);
		this->GetTransform().rotation = 0;
		x += speedX;
		y = A * sin(2 * x);
		physics->SetVelocity(Vec2(x, y)); //box->SetVelocity(Vec2(1.0f, 0) * speed);
	}
}

void RidleyBullet::OnSpawn() //*
{
	Enemy::OnSpawn();
	ridley = GetScene()->FindGameObjectByName("Ridley");
	ridleyPos = ridley->GetTransform().position;
	yMax = ridleyPos.y + 3.5f;
}

void RidleyBullet::Update()
{
	Enemy::Update();
	if (!(this->isFrozen == 0 && this->OnGetDamageDelayTime <= 0)) return;
	lifeTime -= Time::GetDeltaTime();

	if (this->GetTransform().position.y > yMax)
	{
		x = 0;
		x += speedX;
		y = -A * sin(2 * x);
		this->physics->SetVelocity(Vec2(x, y));
	}
	else if (CameraComponent::tiles[(int)(this->GetTransform().position.y - 0.25f)][(int)this->GetTransform().position.x] != -1)
	{
		x = 0;
		x += speedX;
		y = A * sin(2 * x);
		this->physics->SetVelocity(Vec2(x, y));
		A--;
		yMax--;
	}

	if (lifeTime < 0)
	{
		GetScene()->DestroyGameObject(this);
	}

	transform.position += physics->GetVelocity() * Time::GetDeltaTime();
}

void RidleyBullet::OnCollisionEnter(GameObject * other, const Vec2& normal)
{
	Enemy::OnCollisionEnter(other, normal);
	
}

