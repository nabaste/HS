#pragma once

class Entity
{
public:
	Entity() : markedForDeath_(false) {};

	virtual ~Entity() {}
	virtual void update() = 0;
	virtual void lateUpdate() = 0;

	bool markedForDeath_;

private:

};