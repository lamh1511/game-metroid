#include "Zoomer.h"
#include "MetroidContent.h"
#include "ZoomerAnimation.h"
#include "GameFramework\GameComponent\CameraComponent.h"
#include "SamusDamage.h"
#include "MetroidCharacter.h"
#include "EnergyBall.h"
#include "Explosion.h"
#include "SamusAnimation.h"

Zoomer::Zoomer()
{
	Health = 20;
	Damage = 5;
	OnGetDamageDelayTime = 0;
	physics = AddComponent<SimulatePhysics>();
	physics->SetBodySize(Vec2(0.6f, 0.8f));
	physics->SetStatic(false);
	physics->DisableCollision(true);
	physics->SetMass(0);
	animation = AddComponent<AnimationController>();
	animation->AddMainAnimation(MetroidContent::GetObjectByName<Animation>("ZoomerMainAnimation"));

	vx = 3.0f;
	vy = 3.0f;
	rotate = (int)GetTransform().rotation;
	this->ZoomerUpdate = nullptr;
}

void Zoomer::OnSpawn()
{
	Enemy::OnSpawn();
	if (ZoomerUpdate == nullptr) SetZoomerType(2);
}

void Zoomer::Update()
{
	Enemy::Update();
	if(this->isFrozen == 0 && this->OnGetDamageDelayTime <= 0)
	(*this.*ZoomerUpdate)();
}

void Zoomer::OnCollisionEnter(GameObject * other, const Vec2& normal)
{
	Enemy::OnCollisionEnter(other, normal);
}


inline bool checkTile(Vec2 position)
{
	int i = CameraComponent::tiles[(int)position.y][(int)position.x];
	return (i == -1 || i == 40 || i == 36 || i == 37 || i == 320 || i == 321) ? 0 : 1;
}

Zoomer* Zoomer::SetZoomerType(int type)
{
	position = GetTransform().position;
	rotate = 0;
	if (type == 1)
	{
		this->ZoomerUpdate = &Zoomer::Zoomer1;
		endpoint = position + Vec2(-1.0f, 0);
		physics->SetVelocity(Vec2(vx, 0));
	}
	else if (type == 2)
	{
		this->ZoomerUpdate = &Zoomer::Zoomer2;
		endpoint2 = position + Vec2(1.0f, 0);
		physics->SetVelocity(Vec2(vx, 0));
	}
	return this;
}

void Zoomer::Zoomer1()
{
	float dt = (float)Time::GetDeltaTime();

	switch (rotate)
	{
	case 0: {
		position.x -= vx * dt;
		if (endpoint.x >= position.x) {
			position.x = endpoint.x;
			getNewEndPoint(endpoint, rotate);
		}
		break;
	}
	case 90: {
		position.y -= vy * dt;
		if (endpoint.y >= position.y) {
			position.y = endpoint.y;
			getNewEndPoint(endpoint, rotate);
		}
		break;
	}
	case 180: {
		position.x += vx * dt;
		if (endpoint.x <= position.x) {
			position.x = endpoint.x;
			getNewEndPoint(endpoint, rotate);
		}
		break;
	}
	case -90: {
		position.y += vy * dt;
		if (endpoint.y <= position.y) {
			position.y = endpoint.y;
			getNewEndPoint(endpoint, rotate);
		}
		break;
	}
	}
	SetTransform(Transform(Vec2(position.x, position.y), (float)rotate));
	//transform.position += physics->GetVelocity() * Time::GetDeltaTime();
	if (rotate == 0)
	{
		physics->SetVelocity(Vec2(-vx, 0));
	}
	else if (rotate == 90)
	{
		physics->SetVelocity(Vec2(0, -vy));
	}
	else if (rotate == -90)
	{
		physics->SetVelocity(Vec2(0, vy));
	}
	else if (rotate == 180)
	{
		physics->SetVelocity(Vec2(vx, 0));
	}
}

void Zoomer::Zoomer2()
{
	float dt = (float)Time::GetDeltaTime();

	switch (rotate)
	{
	case 0: {
		position.x += vx * dt;
		if (endpoint2.x <= position.x) {
			position.x = endpoint2.x;

			getNewEndPoint2(endpoint2, rotate);
		}
		break;
	}
	case 90: {
		position.y += vy * dt;
		if (endpoint2.y <= position.y) {
			position.y = endpoint2.y;
			getNewEndPoint2(endpoint2, rotate);
		}
		break;
	}
	case 180: {
		position.x -= vx * dt;
		if (endpoint2.x >= position.x) {
			position.x = endpoint2.x;
			getNewEndPoint2(endpoint2, rotate);
		}
		break;
	}
	case -90: {
		position.y -= vy * dt;
		if (endpoint2.y >= position.y) {
			position.y = endpoint2.y;
			getNewEndPoint2(endpoint2, rotate);
		}
		break;
	}
	}
	SetTransform(Transform(Vec2(position.x, position.y), (float)rotate));
	if (rotate == 0)
	{
		physics->SetVelocity(Vec2(vx, 0));
	}
	else if (rotate == 90)
	{
		physics->SetVelocity(Vec2(0, vy));
	}
	else if (rotate == -90)
	{
		physics->SetVelocity(Vec2(0, -vy));
	}
	else if (rotate == 180)
	{
		physics->SetVelocity(Vec2(-vx, 0));
	}
}

void Zoomer::getNewEndPoint(Vec2& endpoint, int& rotate) {
	switch (rotate) {
	case 0: {
		bool m = checkTile(Vec2(endpoint.x - 1.0f, endpoint.y));
		bool n = checkTile(Vec2(endpoint.x, endpoint.y - 1.0f));
		if (n == 0) {
			rotate = 90;
			endpoint.y -= 1.0f;
			break;

		}
		else {
			if (m != 0) {
				rotate = -90;
				endpoint.y += 1.0f;
				break;
			}
			else {
				endpoint.x -= 1.0f;
				break;
			}
		}
	}
	case 90: {
		bool n = checkTile(Vec2(endpoint.x + 1.0f, endpoint.y));
		bool m = checkTile(Vec2(endpoint.x, endpoint.y - 1.0f));
		if (n == 0) {
			rotate = 180;
			endpoint.x += 1.0f;
			break;

		}
		else {
			if (m != 0) {
				rotate = 0;
				endpoint.x -= 1.0f;
				break;
			}
			else {
				endpoint.y -= 1.0f;
				break;
			}
		}
	}
	case 180: {
		bool m = checkTile(Vec2(endpoint.x + 1.0f, endpoint.y));
		bool n = checkTile(Vec2(endpoint.x, endpoint.y + 1.0f));
		if (n == 0) {
			rotate = -90;
			endpoint.y += 1.0f;
			break;

		}
		else {
			if (m != 0) {
				rotate = 90;
				endpoint.y -= 1.0f;
				break;
			}
			else {
				endpoint.x += 1.0f;
				break;
			}
		}
	}
	case -90: {
		bool n = checkTile(Vec2(endpoint.x - 1.0f, endpoint.y));
		bool m = checkTile(Vec2(endpoint.x, endpoint.y + 1.0f));
		if (n == 0) {
			rotate = 0;
			endpoint.x -= 1.0f;
			break;

		}
		else {
			if (m != 0) {
				rotate = 180;
				endpoint.x += 1.0f;
				break;
			}
			else {
				endpoint.y += 1.0f;
				break;
			}
		}
	}
	}

}

void Zoomer::getNewEndPoint2(Vec2& endpoint2, int& rotate) {
	switch (rotate) {
	case 0: {
		bool m = checkTile(Vec2(endpoint2.x + 1.0f, endpoint2.y));
		bool n = checkTile(Vec2(endpoint2.x, endpoint2.y - 1.0f));
		if (n == 0) {
			rotate = -90;
			endpoint2.y -= 1.0f;
			break;

		}
		else {
			if (m != 0) {
				rotate = 90;
				endpoint2.y += 1.0f;
				break;
			}
			else {
				endpoint2.x += 1.0f;
				break;
			}
		}
	}
	case 90: {
		bool n = checkTile(Vec2(endpoint2.x + 1.0f, endpoint2.y));
		bool m = checkTile(Vec2(endpoint2.x, endpoint2.y + 1.0f));
		if (n == 0) {
			rotate = 0;
			endpoint2.x += 1.0f;
			break;

		}
		else {
			if (m != 0) {
				rotate = 180;
				endpoint2.x -= 1.0f;
				break;
			}
			else {
				endpoint2.y += 1.0f;
				break;
			}
		}
	}
	case 180: {
		bool m = checkTile(Vec2(endpoint2.x - 1.0f, endpoint2.y));
		bool n = checkTile(Vec2(endpoint2.x, endpoint2.y + 1.0f));
		if (n == 0) {
			rotate = 90;
			endpoint2.y += 1.0f;
			break;

		}
		else {
			if (m != 0) {
				rotate = -90;
				endpoint2.y -= 1.0f;
				break;
			}
			else {
				endpoint2.x -= 1.0f;
				break;
			}
		}
	}
	case -90: {
		bool n = checkTile(Vec2(endpoint2.x - 1.0f, endpoint2.y));
		bool m = checkTile(Vec2(endpoint2.x, endpoint2.y - 1.0f));
		if (n == 0) {
			rotate = 180;
			endpoint2.x -= 1.0f;
			break;

		}
		else {
			if (m != 0) {
				rotate = 0;
				endpoint2.x += 1.0f;
				break;
			}
			else {
				endpoint2.y -= 1.0f;
				break;
			}
		}
	}
	}
}
