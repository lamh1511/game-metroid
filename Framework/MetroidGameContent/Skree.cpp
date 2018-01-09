#include "Skree.h"
#include "SkreeAnimation.h"
#include "GameFramework\GameComponent\CameraComponent.h"
#include "MetroidContent.h"
#include "SkreeBall.h"
#include "MetroidCharacter.h"

Skree::Skree()
{
	this->name = "Skree";
	physics = AddComponent<SimulatePhysics>();
	physics->SetBodySize(Vec2(0.6f, 1.4f));
	physics->SetStatic(false);
	physics->DisableCollision(true);
	physics->SetMass(0);

	animation = AddComponent<AnimationController>();
	animation->AddMainAnimation( MetroidContent::GetObjectByName<Animation>("SkreeMainAnimation"));
	vx = 4.5f;
	vy = 6.5f;
	flag1 = 0;
	flag2 = 0;

	DestroyDelayTime = 0.3;

	Health = 20;
}


Skree::~Skree()
{
}

void Skree::OnSpawn()
{
	Enemy::OnSpawn();
}

void Skree::Update()
{
	Enemy::Update();
	if (!(this->isFrozen == 0 && this->OnGetDamageDelayTime <= 0)) return;
	float dt = (float)Time::GetDeltaTime();
	Vec2 samus_position = Samus->GetTransform().position;

	if (std::abs(samus_position.x - position.x) <= 4.0f) {
		flag1 = 1;
	}
	if (flag1 > 0) {
		if (flag2 == 0)
		{
			position.y -= vy * dt;
			physics->SetVelocityY(-vy);
			if (position.x > samus_position.x) {
				position.x -= vx * dt;
				if (position.x <= samus_position.x) {
					position.x = samus_position.x;
				}
				physics->SetVelocityX(-vx);
			}
			else {
				position.x += vx * dt;
				if (position.x >= samus_position.x) {
					position.x = samus_position.x;
				}
				physics->SetVelocityX(-vx);
			}
			if (CheckLeftTile(position) != 0) {
				//position.x = checkLeftTile(position);
				//flag2 = 1;
			}
			if (CheckRightTile(position) != 0) {
				//position.x = checkRightTile(position);
				//flag2 = 1;
			}
		}

		if (CheckBottomTile(position) != 0) {
			//position.y = checkBottomTile(position);
			flag2 = 1;
			physics->SetVelocity(Vec2(0, 0));
		}
	}
	SetTransform(Transform(Vec2(position.x, position.y), 0));
	if (flag2 == 1) // Ban dau = 2.0; Khi cham dat = 2, sau do giam dan, < 0 se no.
	{
		DestroyDelayTime -= Time::GetDeltaTime();
		if (DestroyDelayTime <= 0)
		{
			GetScene()->DestroyGameObject(this);
			SkreeBall::Explose(this->transform.position, this->scene);
		}
	}
}

void Skree::OnCollisionEnter(GameObject * other, const Vec2 & normal)
{
	Enemy::OnCollisionEnter(other, normal);
}

