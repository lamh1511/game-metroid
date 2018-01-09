#include "SamusDamage.h"
#include "MetroidContent.h"
#include "SamusAnimation.h"
#include "MetroidCharacter.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Bomb.h"
#include "SamusWaveBeam.h"

Vec2 SamusWaveBeamPos = Vec2();
Vec2 SamusWaveBeamDir = Vec2();

SamusDamage::SamusDamage(const Vec2& position, const Vec2& direction, void (SamusDamage::*Type)()) :
	GameObject(Transform(position), "SamusDamage", "SamusDamage", true),// duoc dieu khien boi physic
	Type(Type),
	lifeTime(0.3),
	speed(18.0f)
{
	if (this->Type == &SamusDamage::SamusBomb || this->Type == &SamusDamage::WaveBeam)
	{
		if (this->Type == &SamusDamage::WaveBeam)
		{
			SamusWaveBeamDir = direction;
			SamusWaveBeamPos = position;
		}
		return;
	}
	sprite = AddComponent<SpriteRenderer>();
	sprite->SetDrawOrder(0);
	physic = AddComponent<SimulatePhysics>();
	physic->SetStatic(false);
	physic->DisableCollision(false);
	physic->SetMass(0);
	if (this->Type == &SamusDamage::NormalBeam)
	{
		sprite->SetSprite(MetroidContent::GetObjectByName<Sprite>("TileSet_25"));
		physic->SetBodySize(Vec2(0.2f, 0.2f));
		damage = 5;
	}
	else if (Type == &SamusDamage::IceBeam)
	{
		this->name = "IceBeam";
		sprite->SetSprite(MetroidContent::GetObjectByName<Sprite>("TileSet_74"));
		physic->SetBodySize(Vec2(0.1f, 0.1f));
		damage = 7;
	}
	else if (Type == &SamusDamage::MissileRocket)
	{
		this->name = "MissileRocket";
		sprite->SetSprite(MetroidContent::GetObjectByName<Sprite>("TileSet_70"));
		physic->SetBodySize(Vec2(0.3f, 0.3f));
		damage = 15;
	}
	else if (Type == &SamusDamage::SamusBomb)
	{
		sprite->SetSprite(MetroidContent::GetObjectByName<Sprite>("TileSet_25"));
		physic->SetBodySize(Vec2(0.2f, 0.2f));
	}
	else if (Type == &SamusDamage::WaveBeam)
	{
		//sprite->SetSprite(MetroidContent::GetObjectByName<Sprite>("TileSet_91"));
	}
	if (direction.x > 0)
	{
		physic->SetVelocity(Vec2(1.0f, 0) * speed);
	}
	else if (direction.x < 0)
	{
		this->GetTransform().scale.x *= -1.0f;
		physic->SetVelocity(Vec2(-1.0f, 0) * speed);
	}
	else
	{
		this->GetTransform().rotation = 90.0f;
		physic->SetVelocity(Vec2(0, 1.0f) * speed);
	}
}


void SamusDamage::OnSpawn()
{
	Samus = static_cast<MetroidCharacter*>(GetScene()->FindGameObjectByName("Samus"));
	if (Samus->longBeamEnabled) lifeTime = 0.8;
	if (this->Type == &SamusDamage::SamusBomb )
	{
		if (Samus->animation->currentAnimation == Samus->animation->roll) scene->SpawnNewGameObject<Bomb>(Transform(Vec2(transform.position - Vec2(0, 0.5f))));
		scene->DestroyGameObject(this);
		return;
	}
	else if (this->Type == &SamusDamage::WaveBeam)
	{
		scene->SpawnNewGameObject(new SamusWaveBeam(SamusWaveBeamDir, SamusWaveBeamPos));
		scene->DestroyGameObject(this);
		return;
	}
}

void SamusDamage::Update()
{
	if (this->Type == &SamusDamage::SamusBomb || this->Type == &SamusDamage::WaveBeam)
	{
		return;
	}
	GameObject::Update();
	lifeTime -= Time::GetDeltaTime();
	if (lifeTime < 0)
	{
		GetScene()->DestroyGameObject(this);
	}
}

void SamusDamage::OnCollisionEnter(GameObject * other, const Vec2 & normal)
{
	if (this->Type == &SamusDamage::SamusBomb || this->Type == &SamusDamage::WaveBeam) return;
	if (this->Type == &SamusDamage::MissileRocket)
	{
		scene->SpawnNewGameObject<Explosion>(Transform(Vec2(transform.position)));
		scene->DestroyGameObject(this);
	}
	if (other->GetTag() == "Enemy")
	{
		Enemy* enemy = static_cast<Enemy*>(other);
		if (enemy->Health > 0)
		{
			enemy->Health -= damage;
		}
		// Kiem tra loai sat thuong damage
		if (this->Type == &SamusDamage::IceBeam)
		{
			enemy->Freeze();
		}
		scene->DestroyGameObject(this);
	}
	if (other->GetTag() == "Terrain") scene->DestroyGameObject(this);
	
}

void SamusDamage::IceBeam()
{
}

void SamusDamage::MissileRocket()
{
}

void SamusDamage::LongBeam()
{
}

void SamusDamage::SamusBomb()
{
}

void SamusDamage::WaveBeam()
{
}

void SamusDamage::NormalBeam()
{
}