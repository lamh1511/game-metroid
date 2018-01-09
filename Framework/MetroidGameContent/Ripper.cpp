#include "Ripper.h"
#include "MetroidContent.h"



Ripper::Ripper()
{
	this->name = "Ripper";
	Health = 999999;
	physics = AddComponent<SimulatePhysics>();
	physics->SetBodySize(Vec2(0.8f, 0.2f));
	physics->SetStatic(false);
	physics->DisableCollision(true);
	physics->SetMass(0);

	animation = AddComponent<AnimationController>();
	animation->AddMainAnimation(MetroidContent::GetObjectByName<Animation>("RipperAnimation"));
	moveLeftVelo = -5.f;
	moveRightVelo = 5.f;

	isMoveLeft = true;
	isMoveRight = false;
	vx = moveLeftVelo;
	scale = 1.f;
}


Ripper::~Ripper()
{
}

void Ripper::OnSpawn()
{
	Enemy::OnSpawn();
	
}

void Ripper::Update()
{
	Health = 1000;
	Enemy::Update();
	if (!(this->isFrozen == 0 && this->OnGetDamageDelayTime <= 0)) return;
	float dt = (float)Time::GetDeltaTime();
	if (isMoveLeft) {
		if (CheckLeftTile(position)) {
			isMoveLeft = false;
			isMoveRight = true;
			vx = moveRightVelo;
			scale = -1.f;
		}
	}
	else if (isMoveRight) {
		if (CheckRightTile(position)) {
			isMoveLeft = true;
			isMoveRight = false;
			vx = moveLeftVelo;
			scale = 1.f;
		}
	}
	position.x += vx * dt;
	physics->SetVelocity(Vec2(vx, vy));
	//transform.position.x  = position.x;
	SetTransform(Transform(Vec2(position.x, position.y), 0, Vec2(scale,1)));

}

void Ripper::OnCollisionEnter(GameObject * other, const Vec2& normal)
{
	Enemy::OnCollisionEnter(other, normal);
}