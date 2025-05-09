#include "Tree.h"
#include <algorithm>
#include <iostream>

void Bird::update()
{
	eat();
	grow();
	if (life_ > matingThreshold_) {
		if (!mate()) move();
	}
	else move();
}

void Bird::lateUpdate()
{
	dieOfOldAge();
}

void Bird::eat()
{
	std::map<std::shared_ptr<Bird>, std::shared_ptr<Branch>>& birdPos = Tree::instance().birdPositions;
	std::for_each(birdPos.begin(), birdPos.end(), [this](auto& p) {
		auto& [key, value] = p;
		if (key.get() == this) {
			value->looseLife(foodConsumedPerTurn_);
		}
		});
}

void Bird::grow()
{
	life_ += LIFE_GROWTH_PER_TURN;
	age_++;
}

bool Bird::mate()
{
	bool mated = false;
	std::map<std::shared_ptr<Bird>, std::shared_ptr<Branch>>& birdPos = Tree::instance().birdPositions;
	std::for_each(birdPos.begin(), birdPos.end(), [this, birdPos, &mated](auto& p) {
		auto& [key, value] = p;
		if (key.get() == this) return;
		if (key->life() > matingThreshold_)
		{
			std::shared_ptr<Bird> newBirdPtr = std::make_shared<Bird>(birdPos.size()+1);
			Tree::instance().subscribeToUpdate(newBirdPtr);
			Tree::instance().birdPositions[newBirdPtr] = value;
			key->getMated();
			life_ = LIFE_AFTER_MATING;
			mated = true;
		}
	});
	return mated;
}

void Bird::move()
{
	for (auto it = Tree::instance().birdPositions.begin(); it != Tree::instance().birdPositions.end(); ) {
		if (it->first.get() == this && it->second->life() < minBranchLife_) 
		{
			std::shared_ptr<Branch> newPosition = Tree::instance().getLiveliestBranch();
			if (newPosition) {
				it->second = newPosition;
				++it;
			} else {
				// If no valid branch is found, the bird dies
				markedForDeath_ = true;
				std::cout << "Bird " << name_ << " has died - no branches left to perch on" << std::endl;
				it = Tree::instance().birdPositions.erase(it);
			}
		} else {
			++it;
		}
	}
}

void Bird::getMated()
{
	life_ = LIFE_AFTER_MATING;
}

void Bird::dieOfOldAge()
{
	if (age_ > lifeExpectancy_)
	{
		markedForDeath_ = true;
	}
}