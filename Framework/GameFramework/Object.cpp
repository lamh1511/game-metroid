#include "Object.h"

std::list<int> Object::UniqueID = std::list<int>();

Object::Object():
	name("None"),
	ID(GenerateUniqueID())
{
}

Object::Object(const std::string& name) :
	name(name),
	ID(GenerateUniqueID())
{
}

Object::~Object()
{
	Object::UniqueID.remove(this->ID);
}

void Object::SetName(const std::string & name)
{
	this->name = name;
}

const std::string & Object::GetName() const
{
	return this->name;
}

int Object::GetObjectID() const
{
	return this->ID;
}

int Object::GenerateUniqueID()
{
	int num;
	bool isValid;
	do
	{
		num = 0;
		isValid = true;
		for (int i = 1; i <= 5; i++)
		{
			num += (rand() * i);
		}
		for (int i : Object::UniqueID)
		{
			if (num == i)
			{
				isValid = false;
				break;
			}
		}
	} while (!isValid);
	Object::UniqueID.push_back(num);
	return num;
}

