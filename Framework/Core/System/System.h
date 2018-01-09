#pragma once

class System
{
public:
	System();
	virtual ~System();
public:
	System(const System&) = delete;
	System& operator=(const System&) = delete;
public:
	virtual bool Initialize() = 0;
	virtual void Update() = 0;
	virtual bool Shutdown() = 0;
};

