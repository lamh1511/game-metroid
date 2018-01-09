#pragma once
#include <string>
#include "Utilities\Utilities.h"

class IGraphics
{
public:
	IGraphics() {};
	virtual ~IGraphics() {};
public:
	virtual bool CreateTextureFromFile(const std::string& fileName, const ARGB& colorKey, int textureID) = 0;
	virtual void RemoveTexture(int textureID) = 0;
	virtual void GetImageInfoFromFile(const std::string& fileName, int& width, int& height) = 0;
	virtual void AddToDrawQueue(const Transform& transform, int textureID, const Rect& rect, float pixelsPerUnit, int sortingOrder, const ARGB& color) = 0;
	virtual void ClearDrawQueue() = 0;
protected:
	virtual void RenderBegin() = 0;
	virtual void RenderDrawQueue() = 0;
	virtual void Draw(const Transform& transform, int textureID, const Rect& rect, float pixelsPerUnit, const ARGB& color) = 0;
	virtual void RenderEnd() = 0;
public:
	virtual void SetViewPosition(const Vec2& position) = 0;
	virtual void SetViewSize(const Vec2& viewSize) = 0;
	virtual void SetViewport(unsigned long x, unsigned long y, unsigned long width, unsigned long height, float MinZ, float MaxZ) = 0;
};

