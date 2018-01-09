#pragma once
#include "Utilities\Utilities.h"
#include <string>
#include <list>

class Object
{
public:
	Object();
	Object(const std::string& name);
	virtual ~Object();
public:
	Object(const Object&) = delete;
	Object& operator=(const Object&) = delete;
	bool operator ==(const Object &other) const = delete;
	bool operator !=(const Object &other) const = delete;
public:
	void SetName(const std::string& name);
	const std::string& GetName() const;
	int GetObjectID() const;
protected:
	std::string name;
	const int ID;
private:
	static std::list<int> UniqueID;
	static int GenerateUniqueID();
};

