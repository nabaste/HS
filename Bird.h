#pragma once
#include <iostream>

#include "Entity.h"
#include "Branch.h"
class Bird :   public Entity
{
public:
	Bird(int name): age_(0), name_(name), lifeExpectancy_(30), life_(100.00), foodConsumedPerTurn_(1.8), matingThreshold_(115.00), minBranchLife_(13.00)
	{}

	void update();
	void lateUpdate();

	int const age() { return age_; }
	int const name() { return name_; }
	int const lifeExpectancy() { return lifeExpectancy_; }
	double const life() { return life_; }

	void grow();
	void eat();
	bool mate();
	void move();
	void getMated();
	void dieOfOldAge();

private:
	int age_;
	int name_;
	int lifeExpectancy_;
	double life_;
	double foodConsumedPerTurn_;
	double matingThreshold_;
	double minBranchLife_;
};

