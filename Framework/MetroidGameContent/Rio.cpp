#include "Rio.h"
#include "ZoomerAnimation.h"
#include "GameFramework\GameComponent\CameraComponent.h"
#include "MetroidContent.h"
#include "RioAnimation.h"
#include "MetroidCharacter.h"

Rio::Rio()
{
	this->name = "Rio";

	physics = AddComponent<SimulatePhysics>();
	physics->SetBodySize(Vec2(0.6f, 0.6f));
	physics->SetStatic(false);
	physics->DisableCollision(true);
	physics->SetMass(0);

	animation = AddComponent<AnimationController>();
	animation->AddMainAnimation(MetroidContent::GetObjectByName<Animation>("RioMainAnimation"));
	vx = 0.0f;
	vy = 0.0f;
	flag = 0;
	Health = 30;
}


Rio::~Rio()
{
}

void Rio::OnSpawn()
{
	Enemy::OnSpawn();

	_rightDownVelo = rightDownVelo = Vector2(5, -20);
	_leftDownVelo = leftDownVelo = Vector2(-5, -20);
	deacceleration = (float)0.2;

	_rightUpVelo = rightUpVelo = Vector2(2, (float)0.05);
	_leftUpVelo = leftUpVelo = Vector2(-2, (float)0.05);
	acceleration = (float)0.5;

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
//
//float CheckLeftTile(Vec2& position) {
//	int i = CameraComponent::tiles[(int)(position.y)][(int)(position.x - 0.5f)];
//	if (i != -1) {
//		position.x = (int)(position.x - 0.5f) + 1.5f;
//		return 1;
//	}
//	else
//		return 0;
//}
//
//float CheckRightTile(Vec2& position) {
//	int i = CameraComponent::tiles[(int)(position.y)][(int)(position.x + 0.45f)];
//	if (i != -1) {
//		position.x = (int)(position.x + 0.45f) - 0.5f;
//		return 1;
//	}
//	else
//		return 0;
//}

void Rio::Update()
{
	Enemy::Update();
	if (!(this->isFrozen == 0 && this->OnGetDamageDelayTime <= 0)) return;
	float dt = (float)Time::GetDeltaTime();
	Vec2 samus_position = Samus->GetTransform().position;

	float distance = std::abs(samus_position.x - position.x);
	if (flag == 0) {
		if (distance <= 4.0f) {
			flag = 1;
			if (samus_position.x < position.x) {
				state = 1;
			}
			else {
				state = 3;
			}
		}
	}

	if (flag == 1) {
		switch (state) {
		case 1:	//left down
		{
			vx = leftDownVelo.x;
			vy = leftDownVelo.y;
			leftDownVelo.y -= deacceleration;
			position.x += vx * dt;
			position.y += vy * dt;
			if (CheckLeftTile(position) != 0) {
				leftDownVelo = _leftDownVelo;
				state = 4;
				break;
			}
			if (CheckBottomTile(position) != 0) {
				leftDownVelo = _leftDownVelo;
				state = 5;
			}
			break;
		}
		case 2: {
			vx = leftUpVelo.x;
			vy = leftUpVelo.y;
			leftUpVelo.y += acceleration;
			position.x += vx * dt;
			position.y += vy * dt;
			if (CheckLeftTile(position) != 0) {
				leftUpVelo.x = 0;
			}
			if (CheckTopTile(position) != 0) {
				leftUpVelo = _leftUpVelo; //  tra lai nhu cu
				flag = 0;
			}
			break;
		}
		case 3: {
			vx = rightDownVelo.x;
			vy = rightDownVelo.y;
			rightDownVelo.y -= deacceleration;
			position.x += vx * dt;
			position.y += vy * dt;
			if (CheckRightTile(position) != 0) {
				rightDownVelo = _rightDownVelo;
				state = 2;
				break;
			}
			if (CheckBottomTile(position) != 0) {
				rightDownVelo = _rightDownVelo;
				state = 5;
			}
			break;
		}
		case 4: {
			vx = rightUpVelo.x;
			vy = rightUpVelo.y;
			rightUpVelo.y += acceleration;
			position.x += vx * dt;
			position.y += vy * dt;
			if (CheckRightTile(position) != 0) {
				rightUpVelo.x = 0;
			}
			if (CheckTopTile(position) != 0) {
				rightUpVelo = _rightUpVelo; //  tra lai nhu cu
				flag = 0;
			}
			break;
		}
		case 5: {
			position.x += vx * dt;
			if (vx >= 0) {
				if (distance >= 4.0f || CheckRightTile(position) != 0)
					state = 4;
			}
			else {
				if (distance >= 4.0f || CheckLeftTile(position) != 0)
					state = 2;
			}
			break;
		}
		}
	}
	physics->SetVelocity(Vec2(vx, vy));
	SetTransform(Transform(Vec2(position.x, position.y), 0));
}

void Rio::OnCollisionEnter(GameObject * other, const Vec2 & normal)
{
	Enemy::OnCollisionEnter(other, normal);
}
