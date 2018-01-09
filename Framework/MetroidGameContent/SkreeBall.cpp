#include "SkreeBall.h"
#include "MetroidCharacter.h"
#include "MetroidContent.h"
#include "MetroidCharacter.h"
#include "SamusAnimation.h"

SkreeBall::SkreeBall() :
	angle(0),
	lifeTime(0.15)
{
	this->name = "SkreeBall";
	physics = AddComponent<SimulatePhysics>();
	physics->SetBodySize(Vec2(0.2f, 0.2f));
	physics->SetStatic(false);
	physics->DisableCollision(true);

	animation = AddComponent<AnimationController>();
	animation->AddMainAnimation(MetroidContent::GetObjectByName<Animation>("SkreeExplosion"));
	speed = 14.0f;
}

SkreeBall::~SkreeBall()
{
}

void SkreeBall::SetAngle(float angle)
{
	if (angle == 45.0f)
	{
		physics->SetVelocity(Vec2(speed, speed));
	}
	else if (angle == 90.0f)
	{
		physics->SetVelocity(Vec2(0, speed * 1.41f));
	}
	else if (angle == 135.0f)
	{
		physics->SetVelocity(Vec2(-speed, speed));
	}
	else if (angle == 180.0f)
	{
		physics->SetVelocity(Vec2(-speed * 1.41f, 0));
	}
	else if (angle == 0.0f)
	{
		physics->SetVelocity(Vec2(speed * 1.41f, 0));
	}
}

void SkreeBall::Update()
{
	Enemy::Update();
	if (!(this->isFrozen == 0 && this->OnGetDamageDelayTime <= 0)) return;
	lifeTime -= Time::GetDeltaTime();
	if (lifeTime <= 0) scene->DestroyGameObject(this);
	transform.position += physics->GetVelocity() * (float)Time::GetDeltaTime();
}

void SkreeBall::OnCollisionEnter(GameObject * other, const Vec2 & normal)
{
	this->scene->DestroyGameObject(this);
	Enemy::OnCollisionEnter(other, normal);
	/*if (other->GetTag() == "Player")
	{
		MetroidCharacter* samus = static_cast<MetroidCharacter*>(other);
		if (samus->OnDamageTime <= 0) samus->energy -= 5;

		samus->jumpTime = 0;
		if (samus->OnDamageTime <= 0)
		{

			samus->OnDamage = 1;
			samus->OnDamageTime = 0.3;
			samus->animation->color = ARGB(100, 255, 255, 255);
			if (CameraComponent::tiles[(int)samus->GetTransform().position.y - 1][(int)samus->GetTransform().position.x] == -1)
			{
				samus->CharacterPhysics->SetVelocityY(0.0f);
			}
			else
			{
				if (normal.x == 1.0f)
				{
					samus->CharacterPhysics->SetVelocityX(7.0f);
				}
				else
				{
					samus->CharacterPhysics->SetVelocityX(-7.0f);
				}
			}

		}
	}*/
}

void SkreeBall::Explose(const Vec2& position, Scene *scene)
{
	SkreeBall* ball_0 = scene->SpawnNewGameObject<SkreeBall>(Transform(position));
	ball_0->SetAngle(0);

	SkreeBall* ball_45 = scene->SpawnNewGameObject<SkreeBall>(Transform(position));
	ball_45->SetAngle(45.0f);

	SkreeBall* ball_90 = scene->SpawnNewGameObject<SkreeBall>(Transform(position));
	ball_90->SetAngle(90.0f);

	SkreeBall* ball_135 = scene->SpawnNewGameObject<SkreeBall>(Transform(position));
	ball_135->SetAngle(135.0f);

	SkreeBall* ball_180 = scene->SpawnNewGameObject<SkreeBall>(Transform(position));
	ball_180->SetAngle(180.0f);

}
