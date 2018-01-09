#pragma once
#include "GameFramework\Object.h"

class Texture final : public Object
{
public:
	Texture();
	Texture(const std::string& path, ARGB colorKey, const std::string& name);
	~Texture();
public:
	static bool LoadTextureFromFile(const std::string & path, const ARGB& colorKey, const std::string& name);
protected:
	int width;
	int height;
	ARGB colorKey;
	std::string path;
};

