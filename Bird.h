#pragma once
#include <iostream>

#include "Entity.h"
#include "Branch.h"
class Bird :   public Entity
{
public:
	// Constants for bird mechanics
	static constexpr int DEFAULT_LIFE_EXPECTANCY = 30;
	static constexpr double INITIAL_LIFE = 100.00;
	static constexpr double FOOD_CONSUMED_PER_TURN = 1.8;
	static constexpr double MATING_THRESHOLD = 115.00;
	static constexpr double MIN_BRANCH_LIFE = 13.00;
	static constexpr double LIFE_GROWTH_PER_TURN = 5.3;
	static constexpr double LIFE_AFTER_MATING = 70.00;

	Bird(int name): age_(0), name_(name), lifeExpectancy_(DEFAULT_LIFE_EXPECTANCY), 
        life_(INITIAL_LIFE), foodConsumedPerTurn_(FOOD_CONSUMED_PER_TURN), 
        matingThreshold_(MATING_THRESHOLD), minBranchLife_(MIN_BRANCH_LIFE)
	{}

	void update();
	void lateUpdate();

	int age() const { return age_; }
	int name() const { return name_; }
	int lifeExpectancy() const { return lifeExpectancy_; }
	double life() const { return life_; }

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

