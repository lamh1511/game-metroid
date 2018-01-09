#include "Zeb.h"
#include "ZoomerAnimation.h"
#include "GameFramework\GameComponent\CameraComponent.h"
#include "MetroidContent.h"
#include "MetroidCharacter.h"

Zeb::Zeb()
{
	this->name = "Zeb";
	physics = AddComponent<SimulatePhysics>();
	physics->SetBodySize(Vec2(1.0f, 1.0f));
	physics->SetStatic(false);
	physics->DisableCollision(true);
	physics->SetMass(0);
	
	animation = AddComponent<AnimationController>();
	animation->AddMainAnimation(MetroidContent::GetObjectByName<Animation>("ZebAnimation"));

	moveRightVelo = 8.0f;
	moveLeftVelo = -8.0f;
	vx = moveLeftVelo;
	vy = 8.0f;
	flag = 0;

	delayTime = 2.5;
	countTime = 0;
	lifeTime = 5.0;

	Health = 20;
	scale = 1;
}


Zeb::~Zeb()
{
}

void Zeb::OnSpawn()
{
	Enemy::OnSpawn();
	/*SetTransform(Transform(Vec2(48.5f, 77.5f), 0));
	startPosition = position = Vec2(48.5f, 77.5f);*/
	//position = GetTransform().position;
	startPosition = position;


}

//float CheckTopTile(Vec2& position) {
//	int i = CameraComponent::tiles[(int)(position.y + 0.5f)][(int)(position.x)];
//	if (i != -1) {
//		position.y = (int)(position.y + 0.5f) - 0.5f;
//		return 1;
//	}
//	else
//		return 0;
//}
//
//float CheckBottomTile(Vec2& position) {
//	int i = CameraComponent::tiles[(int)(position.y - 0.5f)][(int)(position.x)];
//	if (i != -1) {
//		position.y = (int)(position.y - 0.5f) + 1.5f;
//		return 1;
//	}
//	else
//		return 0;
//}

//int CheckLeftTile(Vec2& position) {
//	int i = CameraComponent::tiles[(int)(position.y)][(int)(position.x - 0.5f)];
//	if (i != -1) {
//		position.x = (int)(position.x - 0.5f) + 1.5f;
//		return 1;
//	}
//	else
//		return 0;
//}
//
//int CheckRightTile(Vec2& position) {
//	int i = CameraComponent::tiles[(int)(position.y)][(int)(position.x + 0.45f)];
//	if (i != -1) {
//		position.x = (int)(position.x + 0.45f) - 0.5f;
//		return 1;
//	}
//	else
//		return 0;
//}

void Zeb::Update()
{
	Enemy::Update();
	if (!(this->isFrozen == 0 && this->OnGetDamageDelayTime <= 0)) return;
	float dt = (float)Time::GetDeltaTime();
	Vec2 samus_position = Samus->GetTransform().position;
	
	countTime += dt;

	float distance = std::abs(samus_position.x - position.x);
	if (flag == 0) {
		if (distance <= 2.0f) {
			flag = 1;
		}
	}

	if (flag == 1) {
		position.y += vy * dt;
		if (position.y >= samus_position.y) {
			flag = 5;
		}
		//physics->SetVelocityY(vy);
	}
	if (flag == 5) {
		if (countTime >= delayTime)
		{
			if (samus_position.x <= position.x) {
				vx = moveLeftVelo;
				scale = 1;
			}
			else {
				vx = moveRightVelo;
				scale = -1;
			}
			//physics->SetVelocityX(vx);
			flag = 3;
		}
		//position.x += vx * dt;
			//flag = 2;
	}
	//if (flag == 2) {
	//	if (samus_position.x <= position.x) {
	//		vx = moveLeftVelo;
	//	}
	//	else {
	//		vx = moveRightVelo;
	//	}
	//	//physics->SetVelocityX(vx);
	//	flag = 3;
	//}
	if (flag == 3) {
		position.x += vx * dt;
		/*if (CheckLeftTile(position) || CheckRightTile(position)) {
			GetScene()->DestroyGameObject(this);
			flag = 4;
		}*/
		if (lifeTime <= countTime)
		{
		GetScene()->DestroyGameObject(this);
		}
	}
	
	std::cout << position.x << "	" << position.y << std::endl;
	physics->SetVelocity(Vec2(vx, vy));
	/*if (lifeTime <= countTime)
	{
		GetScene()->DestroyGameObject(this);
	}*/

	SetTransform(Transform(Vec2(position.x, position.y), 0, Vec2(scale, 1.f)));
}

void Zeb::OnCollisionEnter(GameObject * other, const Vec2 & normal)
{
	Enemy::OnCollisionEnter(other, normal);
}

