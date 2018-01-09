#include "KraidBullet.h"
#include "MetroidContent.h"
#include "Kraid.h"
#include "GameFramework\GameComponent\CameraComponent.h"

KraidBullet::KraidBullet() :
	lifeTime(4.2),
	speedX(0.1f)
{
	this->name = "KraidBullet";

	animation = AddComponent<AnimationController>();
	animation->AddMainAnimation(MetroidContent::GetObjectByName<Animation>("KraidBulletAnimation"));

	physics = AddComponent<SimulatePhysics>();
	physics->SetBodySize(Vec2(0.2f, 0.2f));
	physics->SetStatic(false);
	physics->DisableCollision(true);
	physics->SetMass(0);

	//AddComponent<RidleyBulletAnimation>(); //*
	shootingTimer = 0; timeout = 0;
	shoot = 0;
	x = 0;
}


KraidBullet::~KraidBullet()
{
}

void KraidBullet::Fire(const Vec2 & firePosition, float direction)
{
	//this->SetTransform(Transform(firePosition));
	this->firePosition = firePosition;

	this->direction = direction;

	//Nạp đạn
	this->SetTransform(Transform(Vec2(kraidPos.x, kraidPos.y), 0, Vec2(direction, 1.0f)));

	/*if (direction == 1.0f)
	{
		this->GetTransform().scale = Vec2(1.0f, 1.0f);
		this->GetTransform().rotation = 0;
		x += speedX;
		box->SetVelocity(Vec2(x, 0));
	}
	else
	{
		this->GetTransform().scale = Vec2(-1.0f, 1.0f);
		this->GetTransform().rotation = 0;
		x -= speedX;
		box->SetVelocity(Vec2(x, 0));
	}*/
}

void KraidBullet::OnSpawn() //*
{
	Enemy::OnSpawn();
	kraid = GetScene()->FindGameObjectByName("Kraid");
	kraidPos = kraid->GetTransform().position;
}

void KraidBullet::Update()
{
	Enemy::Update();
	if (!(this->isFrozen == 0 && this->OnGetDamageDelayTime <= 0)) return;
	lifeTime -= Time::GetDeltaTime();

	if (this->firePosition.y == 0.0f)
		this->timeout = 2.5;
	else if (this->firePosition.y == 0.4f)
		this->timeout = 2.3;
	else
		this->timeout = 2.7;

	if (shootingTimer > this->timeout)
	{
		shoot = 1;
		shootingTimer = 0;
	}

	kraidPos = kraid->GetTransform().position;

	if (!shoot) {
		shootingTimer += Time::GetDeltaTime(); // đếm thời gian
		this->SetTransform(Transform(Vec2(kraidPos.x + direction * firePosition.x, kraidPos.y + firePosition.y), 0, Vec2(direction, 1.0f)));
	}
	else {

		if (direction == 1.0f) {
			this->GetTransform().scale = Vec2(1.0f, 1.0f);
			this->GetTransform().rotation = 0;
			x += speedX;
			physics->SetVelocity(Vec2(x, 0));
		}
		else {
			this->GetTransform().scale = Vec2(-1.0f, 1.0f);
			this->GetTransform().rotation = 0;
			x -= speedX;
			physics->SetVelocity(Vec2(x, 0));
		}
	}

	if (lifeTime < 0)
	{
		scene->DestroyGameObject(this);
		shoot = 0;
	}

	//SetTransform(Transform(Vec2(this->GetTransform().position.x, this->GetTransform().position.y), 0, Vec2(this->direction, 1.0f))); //*

	float xpos = this->GetTransform().position.x + physics->GetVelocity().x * Time::GetDeltaTime();
	float ypos = this->GetTransform().position.y + physics->GetVelocity().y * Time::GetDeltaTime();
	SetTransform(Transform(Vec2(xpos, ypos), 0, Vec2(this->direction, 1.0f)));
}

void KraidBullet::OnCollisionEnter(GameObject * other, const Vec2& normal)
{
	Enemy::OnCollisionEnter(other, normal);
}