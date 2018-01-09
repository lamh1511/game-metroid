#define _CRT_SECURE_NO_DEPRECATE
#include "CameraComponent.h"
#include "Main\GameSystem.h"
#include "GameFramework\GameObject\GameObject.h"
#include "ResourcesLoader\Rapidjson\document.h"
#include "ResourcesLoader\Rapidjson\filereadstream.h"
#include "GameFramework\GameContent\GameContent.h"
#include "GameFramework\GameContent\Texture.h"
#include "Main\GameSystem.h"

using namespace rapidjson;
int CameraComponent::tiles[285][480];

CameraComponent::CameraComponent(float aspectRatio, float size, const std::string& name) :
	Component(name),
	aspectRatio(aspectRatio),
	size(size),
	originalSize(size),
	rows(285),
	columns(480)
{
	FILE* fp = fopen("TiledBackground.json", "rb"); // non-Windows use "r"
	char readBuffer[200000];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	Document d;
	d.ParseStream(is);
	const Value& array = d["data"];
	int k = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (k < (int)array.Size())
			{
				tiles[rows - 1 - i][j] = array[k].GetInt() - 1;
			}
			k++;
		}
	}
	int count = 0;
	for (float i = 0; i < 11; i++)
	{
		for (float j = 0; j < 32; j++)
		{
			float x = j * 16;
			float y = i * 16;
			Array[count] = Vec2(x, y);
			count++;
		}
	}
}

Rect CameraComponent::GetTileRect(int count)
{
	Rect rectA;
	int xx = (int)Array[count].x;
	int yy = (int)Array[count].y;
	rectA.left = xx;
	rectA.top = yy;
	rectA.right = xx + 16;
	rectA.bottom = yy + 16;
	return rectA;
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Zoom(float scale)
{
	if (scale <= 0.25f) scale = 0.25f;
	size = originalSize * scale;
	GameSystem::SetViewSize(Vec2(aspectRatio * size, size));
}

void CameraComponent::SetSize(float size)
{
	this->originalSize = size;
	this->size = size;
	GameSystem::SetViewSize(Vec2(aspectRatio * size, size));
}

RectF CameraComponent::GetCameraRect()
{
	return this->cameraRect;
}

void CameraComponent::LateUpdate()
{
	Vec2 position = gameObject->GetTransform().position;
	GameSystem::SetViewPosition(position);
	cameraRect = RectF(position.y + size / 2.0f, position.y - size / 2.0f, position.x - size * aspectRatio / 2.0f, position.x + size * aspectRatio / 2.0f);

	int top = (int)(cameraRect.top);
	int bottom = (int)(cameraRect.bottom);
	int left = (int)(cameraRect.left);
	int right = (int)(cameraRect.right);

	for (float i = (float)bottom; i <= (float)top; i += 1.0f)
	{
		for (float j = (float)left; j <= (float)right; j += 1.0f)
		{
			if (tiles[(int)i][(int)j] == -1) continue;
			GameSystem::Draw(Transform(Vec2(j + 0.5f, i + 0.5f)), tex->GetObjectID(), GetTileRect(tiles[(int)i][(int)j]), 16.0f, 1);
		}
	}
}

void CameraComponent::OnSpawn()
{
	GameSystem::SetViewSize(Vec2(size * aspectRatio, size));
	GameSystem::SetViewPosition(this->gameObject->GetTransform().position);
	cameraRect = RectF(gameObject->GetTransform().position.y + size / 2.0f,
		gameObject->GetTransform().position.y - size / 2.0f,
		gameObject->GetTransform().position.x - size * aspectRatio / 2.0f,
		gameObject->GetTransform().position.x + size * aspectRatio / 2.0f);
	cameraWidth = cameraRect.right - cameraRect.left;
	this->tex = GameContent::GetObjectByName<Texture>("TileSet.png");
}