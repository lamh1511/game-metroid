#include "Waver.h"
#include "MetroidContent.h"



Waver::Waver()
{
	this->name = "Waver";
	physics = AddComponent<SimulatePhysics>();
	physics->SetBodySize(Vec2(0.6f, 0.8f));
	physics->SetStatic(false);
	physics->DisableCollision(true);
	physics->SetMass(0);

	animation = AddComponent<AnimationController>();
	animation->AddMainAnimation(MetroidContent::GetObjectByName<Animation>("WaverAnimation"));

	moveRightVelo = 3.0f;
	moveLeftVelo = -3.0f;
	moveUpVelo = 5.f;
	moveDownVelo = -5.f;

	flag = 0;

	deceleration = (float)0.2;
	acceleration = (float)0.2;
	isMoveLeft = true;
	isMoveRight = false;
	isMoveDown = true;
	isMoveUp = false;
	vx = moveLeftVelo;
	vy = moveDownVelo;
	countTime = 0;

	scale = Vec2(1.f, 1.f);

	upRange = transform.position.y + 2.f;
	lowRange = transform.position.y - 2.f;
}

Waver::~Waver()
{
}

void Waver::OnSpawn()
{
	Enemy::OnSpawn();
}

void Waver::Update()
{
	Enemy::Update();
	if (!(this->isFrozen == 0 && this->OnGetDamageDelayTime <= 0)) return;
	float dt = (float)Time::GetDeltaTime();
	if (isMoveLeft) {
		if (CheckLeftTile(position)) {
			isMoveLeft = false;
			isMoveRight = true;
			vx = moveRightVelo;
			scale = Vec2(-1.f, 1.f);
		}
	}
	else if (isMoveRight) {
		if (CheckRightTile(position)) {
			isMoveLeft = true;
			isMoveRight = false;
			vx = moveLeftVelo;
			scale = Vec2(1.f, 1.f);
		}
	}
	position.x += vx * dt;

	if (isMoveDown) {
		vy -= deceleration;
		if (CheckBottomTile(position) || position.y <= lowRange) {
			countTime += dt;
			if (countTime >= 1.5f)
			{
				isMoveDown = false;
				isMoveUp = true;
				vy = moveUpVelo;
				countTime = 0;
			}
		}
	}
	else if (isMoveUp) {
		vy += acceleration;
		if (CheckTopTile(position) || position.y >= upRange) {
			countTime += dt;
			if (countTime >= 1.5f)
			{
				isMoveDown = true;
				isMoveUp = false;
				vy = moveDownVelo;
				countTime = 0;
			}
		}
	}
	position.y += vy * dt;
	physics->SetVelocity(Vec2(vx, vy));
	SetTransform(Transform(Vec2(position.x, position.y), 0, scale));
}

void Waver::OnCollisionEnter(GameObject * other, const Vec2 & normal)
{
	Enemy::OnCollisionEnter(other, normal);
}

