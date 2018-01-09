#include "SimulatePhysics.h"
#include "GameFramework\GameObject\GameObject.h"

SimulatePhysics::SimulatePhysics(const Vec2& bodySize, const Vec2& velocity) :
	bodySize(bodySize),
	bodyRect(RectF(0, 0, 0, 0)),
	velocity(velocity),
	normal(Vec2(0, 0)),
	isTrigger(false),
	mass(1.0f),
	isStatic(true)
{
}

SimulatePhysics::~SimulatePhysics()
{
}

void SimulatePhysics::SetBodySize(const Vec2 & bodySize)
{
	this->bodySize = bodySize;
}

const Vec2 & SimulatePhysics::GetBodySize()
{
	return this->bodySize;
}

const RectF & SimulatePhysics::GetBodyRect()
{
	return this->bodyRect;
}

void SimulatePhysics::SetVelocity(const Vec2 & velocity)
{
	this->velocity = velocity;
}

void SimulatePhysics::SetVelocityX(float vx)
{
	this->velocity.x = vx;
}

void SimulatePhysics::SetVelocityY(float vy)
{
	this->velocity.y = vy;
}

const Vec2 & SimulatePhysics::GetVelocity()
{
	return this->velocity;
}

void SimulatePhysics::SetMass(float mass)
{
	this->mass = mass;
}

void SimulatePhysics::SetStatic(bool isStatic)
{
	this->isStatic = isStatic;
}

bool SimulatePhysics::IsTrigger()
{
	return this->isTrigger;
}

void SimulatePhysics::DisableCollision(bool isTrigger)
{
	this->isTrigger = isTrigger;
}

float SimulatePhysics::SweptAABB(SimulatePhysics * other, float& normalx, float& normaly)
{
	//https://www.gamedev.net/articles/programming/general-and-gameplay-programming/swept-aabb-collision-detection-and-response-r3084
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;
	float xEntry, yEntry;
	float xExit, yExit;

	RectF broadphaseRect = GetSweptBroadphaseBox();
	if (!IsColliding(broadphaseRect, other->GetBodyRect()))
	{
		normalx = 0;
		normaly = 0;
		return 1.0f;
	}
	Vec2 otherV = other->GetVelocity() * (float)Time::GetDeltaTime();
	float vx = velocity.x * (float)Time::GetDeltaTime();
	float vy = velocity.y * (float)Time::GetDeltaTime();
	/*if (otherV != Vec2(0, 0))
	{*/
	vx -= otherV.x;
	vy -= otherV.y;
	//}
	RectF movingGameObjectBody = this->GetBodyRect();// rect cua game object dang co component nay
	RectF otherBody = other->GetBodyRect();

	if (vx > 0.0f)
	{
		xInvEntry = otherBody.left - movingGameObjectBody.right;
		xInvExit = otherBody.right - movingGameObjectBody.left;
	}
	else
	{
		xInvEntry = otherBody.right - movingGameObjectBody.left;
		xInvExit = otherBody.left - movingGameObjectBody.right;
	}

	if (vy > 0.0f)
	{
		yInvEntry = otherBody.bottom - movingGameObjectBody.top;
		yInvExit = otherBody.top - movingGameObjectBody.bottom;
	}
	else
	{
		yInvEntry = otherBody.top - movingGameObjectBody.bottom;
		yInvExit = otherBody.bottom - movingGameObjectBody.top;
	}

	if (vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / vx;
		xExit = xInvExit / vx;
	}

	if (vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / vy;
		yExit = yInvExit / vy;
	}

	float entryTime = max(xEntry, yEntry);
	float exitTime = min(xExit, yExit);

	if (entryTime > exitTime || (xEntry < 0.0f && yEntry < 0.0f) || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0;
		normaly = 0;
		return 1.0f;
	}

	if (xEntry > yEntry)
	{
		if (xInvExit < 0.0f)
		{
			normalx = -1.0f;
			normaly = 0;
		}
		else
		{
			normalx = 1.0f;
			normaly = 0;
		}
	}
	else
	{
		if (yInvExit < 0.0f)
		{
			normalx = 0;
			normaly = -1.0f;
		}
		else
		{
			normalx = 0;
			normaly = 1.0f;
		}
	}
	return entryTime;
}

void SimulatePhysics::HandleCollision(std::vector<SimulatePhysics*>& others)
{
	if ((int)others.size() == 0)
	{
		GetOwner()->Translate(this->velocity * (float)Time::GetDeltaTime());
		return;
	}
	collisionTimeLeft = 1.0f;
	collisionTimeRight = 1.0f;
	collisionTimeTop = 1.0f;
	collisionTimeBottom = 1.0f;
	this->normal = Vec2(0, 0);
	for (SimulatePhysics* box : others)
	{
		float normalx = 0;
		float normaly = 0;
		float t = SweptAABB(box, normalx, normaly);
		///-----------------------------------------
		if (t == 1.0f)
		{
			if (box->gameObject->GetTag() == "Enemy")
			{
				if (IsColliding(this->GetBodyRect(), box->GetBodyRect()))
				{
					Vec2 boxVel = box->GetVelocity();
					if (boxVel.x > 0)
					{
						gameObject->OnCollisionEnter(box->GetOwner(), Vec2(-1.0f, 0));
						box->GetOwner()->OnCollisionEnter(gameObject, Vec2(1.0f, 0));
					}
					else if (boxVel.y > 0)
					{

						gameObject->OnCollisionEnter(box->GetOwner(), Vec2(0, -1.0f));
						box->GetOwner()->OnCollisionEnter(gameObject, Vec2(0, 1.0f));
					}
					else if (boxVel.y < 0)
					{
						gameObject->OnCollisionEnter(box->GetOwner(), Vec2(0, 1.0f));
						box->GetOwner()->OnCollisionEnter(gameObject, Vec2(0, -1.0f));
					}
					else// if (boxVel.x < 0)
					{
						gameObject->OnCollisionEnter(box->GetOwner(), Vec2(1.0f, 0));
						box->GetOwner()->OnCollisionEnter(gameObject, Vec2(-1.0f, 0));
					}
				}
			}
			else if (box->gameObject->GetTag() == "Destructible" || box->gameObject->GetTag() == "Boss" || box->gameObject->GetTag() == "PortalEntrance")
			{
				if (IsColliding(this->GetBodyRect(), box->GetBodyRect()))
				{
					Vec2 boxVel = box->GetVelocity();
					if (boxVel.x > 0)
					{
						gameObject->OnCollisionEnter(box->GetOwner(), Vec2(-1.0f, 0));
						box->GetOwner()->OnCollisionEnter(gameObject, Vec2(1.0f, 0));
					}
					else if (boxVel.y > 0)
					{

						gameObject->OnCollisionEnter(box->GetOwner(), Vec2(0, -1.0f));
						box->GetOwner()->OnCollisionEnter(gameObject, Vec2(0, 1.0f));
					}
					else if (boxVel.y < 0)
					{
						gameObject->OnCollisionEnter(box->GetOwner(), Vec2(0, 1.0f));
						box->GetOwner()->OnCollisionEnter(gameObject, Vec2(0, -1.0f));
					}
					else// if (boxVel.x < 0)
					{
						gameObject->OnCollisionEnter(box->GetOwner(), Vec2(1.0f, 0));
						box->GetOwner()->OnCollisionEnter(gameObject, Vec2(-1.0f, 0));
					}
				}
			}
			continue;
		}

		/*{
			if (IsColliding(this->GetBodyRect(), box->GetBodyRect()))
			{
				if (box->IsTrigger())
				{
					gameObject->OnCollisionEnter(box->GetOwner(), Vec2(normalx, normaly));
					box->gameObject->OnCollisionEnter(gameObject, Vec2(-normalx, -normaly));
					continue;
				}
			}
		}*/
		///-----------------------------------------
		/*if (box->gameObject->GetTag() == "Enemy")
		{
			std::cout << "vx = " << box->GetVelocity().x << "	, vy =" << box->GetVelocity().y << std::endl;
		}*/

		if (box->IsTrigger())
		{
			gameObject->OnCollisionEnter(box->GetOwner(), Vec2(normalx, normaly));
			box->gameObject->OnCollisionEnter(gameObject, Vec2(-normalx, -normaly));
			continue;
		}
		if (normaly == -1.0f)
		{
			normal.y = -1.0f;
			if (t < collisionTimeBottom) collisionTimeBottom = t;
		}
		else if (normaly == 1.0f)
		{
			normal.y = 1.0f;
			if (t < collisionTimeTop) collisionTimeTop = t;
		}
		else if (normalx == -1.0f)
		{
			normal.x = -1.0f;
			if (t < collisionTimeLeft) collisionTimeLeft = t;
		}
		else if (normalx == 1.0f)
		{
			normal.x = 1.0f;
			if (t < collisionTimeRight) collisionTimeRight = t;
		}
		// Goi su kien va cham cua cac object tuong ung
		gameObject->OnCollisionEnter(box->GetOwner(), Vec2(normalx, normaly));
		box->gameObject->OnCollisionEnter(gameObject, Vec2(-normalx, -normaly));
	}
	//------------------//
	if (normal == Vec2(0, 0))
	{
		this->GetOwner()->Translate(this->velocity * (float)Time::GetDeltaTime());
		return;
	}
	if (normal == Vec2(0, -1.0f))
	{
		this->GetOwner()->Translate(Vec2(this->velocity.x, this->velocity.y * collisionTimeBottom) * (float)Time::GetDeltaTime());
		this->velocity.y = 0;
		return;
	}
	if (normal == Vec2(0, 1.0f))
	{
		this->GetOwner()->Translate(Vec2(this->velocity.x, this->velocity.y * collisionTimeTop) * (float)Time::GetDeltaTime());
		this->velocity.y = 0;
		return;
	}
	if (normal == Vec2(1.0f, 0))
	{
		this->GetOwner()->Translate(Vec2(this->velocity.x * collisionTimeRight, this->velocity.y) * (float)Time::GetDeltaTime());
		this->velocity.x = 0;
		return;
	}
	if (normal == Vec2(-1.0f, 0))
	{
		this->GetOwner()->Translate(Vec2(this->velocity.x * collisionTimeLeft, this->velocity.y) * (float)Time::GetDeltaTime());
		this->velocity.x = 0;
		return;
	}
	if (normal == Vec2(1.0f, -1.0f))
	{
		this->GetOwner()->Translate(Vec2(this->velocity.x * collisionTimeRight, this->velocity.y * collisionTimeBottom) * (float)Time::GetDeltaTime());
		this->velocity = Vec2(0, 0);
		return;
	}
	if (normal == Vec2(-1.0f, -1.0f))
	{
		this->GetOwner()->Translate(Vec2(this->velocity.x * collisionTimeLeft, this->velocity.y * collisionTimeBottom) * (float)Time::GetDeltaTime());
		this->velocity = Vec2(0, 0);
		return;
	}
}

RectF SimulatePhysics::GetSweptBroadphaseBox()
{
	RectF rect;
	float vx = this->velocity.x * (float)Time::GetDeltaTime();
	float vy = this->velocity.y * (float)Time::GetDeltaTime();

	rect.top = vy > 0 ? bodyRect.top + vy : bodyRect.top;
	rect.bottom = vy > 0 ? bodyRect.bottom : bodyRect.bottom + vy;
	rect.left = vx > 0 ? bodyRect.left : bodyRect.left + vx;
	rect.right = vx > 0 ? bodyRect.right + vx : bodyRect.right;
	return rect;
}

//bool SimulatePhysics::IsColliding(const RectF& bodyRect, const RectF & otherRect)
//{
//	float left = otherRect.left - bodyRect.right;
//	float top = otherRect.top - bodyRect.bottom;
//	float right = otherRect.right - bodyRect.left;
//	float bottom = otherRect.bottom - bodyRect.top;
//
//	return !(left > 0 || right < 0 || top < 0 || bottom > 0);
//}

bool SimulatePhysics::IsColliding(const RectF& bodyRect, const RectF & otherRect)
{
	return !(bodyRect.right < otherRect.left || bodyRect.left > otherRect.right || bodyRect.top < otherRect.bottom || bodyRect.bottom > otherRect.top);
}

void SimulatePhysics::OnSpawn()
{
	bodyRect.left = this->gameObject->GetTransform().position.x - this->bodySize.x / 2.0f;
	bodyRect.right = this->gameObject->GetTransform().position.x + this->bodySize.x / 2.0f;
	bodyRect.top = this->gameObject->GetTransform().position.y + this->bodySize.y / 2.0f;
	bodyRect.bottom = this->gameObject->GetTransform().position.y - this->bodySize.y / 2.0f;
}

void SimulatePhysics::Update()
{
	if (gameObject->IsControllable() == 1)
	{
		HandleCollision(gameObject->GetScene()->GetCollisionBoxes());
	}
}

void SimulatePhysics::LateUpdate()
{
	if (isStatic) return;
	velocity.y += -9.8f * mass * (float)Time::GetDeltaTime(); // V = Vo + G*T: G la gia toc trong truong, G = 9.8
	bodyRect.left = this->gameObject->GetTransform().position.x - this->bodySize.x / 2.0f;
	bodyRect.right = this->gameObject->GetTransform().position.x + this->bodySize.x / 2.0f;
	bodyRect.top = this->gameObject->GetTransform().position.y + this->bodySize.y / 2.0f;
	bodyRect.bottom = this->gameObject->GetTransform().position.y - this->bodySize.y / 2.0f;
}
