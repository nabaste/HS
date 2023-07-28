#pragma once

class Entity
{
public:
	Entity() = default;

	virtual ~Entity() {}
	virtual void update() = 0;

private:
};