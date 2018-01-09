#include "Utilities.h"


bool ARGB::operator==(const ARGB & other) const
{
	return Alpha == other.Alpha && Red == other.Red && Green == other.Green && Blue == other.Blue;
}

ARGB::ARGB(unsigned long Alpha, unsigned long Red, unsigned long Green, unsigned long Blue):
	Alpha(Alpha),
	Red(Red),
	Green(Green),
	Blue(Blue)
{
}

Transform::Transform() :
	position(Vec2(0, 0)),
	rotation(0),
	scale(Vec2(1.0f, 1.0f))
{
}

Transform::Transform(const Vec2 & position, float rotation, const Vec2 & scale) :
	position(position),
	rotation(rotation),
	scale(scale)
{
}

bool Transform::operator==(const Transform & other) const
{
	return position == other.position && rotation == other.rotation && scale == other.scale;
}

int Random_Int(int min, int max)
{
	return (std::rand() % (max + 1 - min) + min);
}
