#include "Texture.h"
#include "Main\GameSystem.h"
Texture::Texture()
{
}

Texture::Texture(const std::string& path, ARGB colorKey, const std::string& name) :
	Object(name),
	colorKey(colorKey),
	path(path)
{
	GameSystem::GetImageInfo(path, this->width, this->height);
	GameSystem::CreateTexture(path, colorKey, this->ID);
}

Texture::~Texture()
{
	GameSystem::RemoveTexture(this->ID);
}

bool Texture::LoadTextureFromFile(const std::string & path, const ARGB& colorKey, const std::string& name)
{
	//Texture* texture = new Texture(path, colorKey, name);
	return true;
}
