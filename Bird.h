#pragma once
#include <iostream>

#include "Entity.h"
class Bird :   public Entity
{
public:
	Bird(int name): age_(0), name_(name), lifeExpectancy_(5), life_(100.00)
	{}

	void update();

	int age() { return age_; }
	int name() { return name_; }
	int lifeExpectancy() { return lifeExpectancy_; }
	double life() { return life_; }

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

