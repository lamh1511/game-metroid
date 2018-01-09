#pragma once
#include "GameFramework\GameComponent\Component.h"

class Texture;

class CameraComponent final : public Component
{
public:
	CameraComponent(float aspectRatio = 1.25f, float size = 12.5f, const std::string& name = "None");
	~CameraComponent();
	void Zoom(float scale);
	void SetSize(float size);
	static int tiles[285][480];
	RectF GetCameraRect();
	float cameraWidth;
protected:
	void LateUpdate() override;
	void OnSpawn() override;
	float aspectRatio;
	float size;
	float originalSize;
	int rows;
	int columns;
	Texture* tex;
	
	RectF cameraRect;
private:
	inline Rect GetTileRect(int count);
	Vec2 Array[352];
};

