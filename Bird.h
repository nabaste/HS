#pragma once
#include <iostream>

#include "Entity.h"
class Bird :   public Entity
{
public:
	Bird(int name): age_(0), name_(name), lifeExpectancy_(5), life_(100.00), foodConsumedPerTurn_(1.3)
	{}

	void update();

	int const age() { return age_; }
	int const name() { return name_; }
	int const lifeExpectancy() { return lifeExpectancy_; }
	double const life() { return life_; }

	void grow();
	void eat();
	void mate();
	void move();
private:
	int age_;
	int name_;
	int lifeExpectancy_;
	double life_;
	double foodConsumedPerTurn_;
};

