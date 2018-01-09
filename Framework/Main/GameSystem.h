#pragma once
#include "Utilities\Utilities.h"
#include <string>

enum TEXT_TYPE
{
	HP,
	ROCKET_COUNT
};
struct GameSystem
{
	static void Draw(const Transform& transform, int textureID, const Rect& rect, float pixelsPerUnit, int sortingOrder, const ARGB& color = ARGB(255, 255, 255, 255));
	static bool IsKeyDown(unsigned int key);
	static bool IsKeyPressed(unsigned int key);
	static bool IsKeyReleased(unsigned int key);
	static void SetViewPosition(const Vec2& position);
	static void SetViewSize(const Vec2& position);
	static double GetGameSystemTime();
	static double GetDeltaTime();
	static bool CreateTexture(const std::string& fileName, const ARGB& colorKey, int textureID);
	static void RemoveTexture(int textureID);
	static void GetImageInfo(const std::string& fileName, int& width, int& height);
	static void SetText(const std::string & text, TEXT_TYPE type);
	static void SetTextVisibility(bool isVisible);
};

