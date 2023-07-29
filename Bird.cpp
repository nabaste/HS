#include "Tree.h"

void Bird::update()
{
	eat();
	grow();
	if (life_ > 120.00) mate();
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
	life_ += 5.3;
	age_++;
 }

void Bird::mate()
{
	std::map<std::shared_ptr<Bird>, std::shared_ptr<Branch>>& birdPos = Tree::instance().birdPositions;
	std::for_each(birdPos.begin(), birdPos.end(), [this, birdPos](auto& p) {
		auto& [key, value] = p;
		if (key.get() == this) return;
		if (key->life() > 120.00)
		{
			std::shared_ptr<Bird> newBirdPtr = std::make_shared<Bird>(birdPos.size()+1);
			Tree::instance().subscribeToUpdate(newBirdPtr);
			Tree::instance().birdPositions[newBirdPtr] = value;
			key->getMated();
			life_ = 70.00;
		}
		});
}

void Bird::move()
{

}

void Bird::getMated()
{
	life_ = 70.00;
}

//std::shared_ptr<Branch> Bird::getBranch()
//{

	//Not working :(
	//auto a = std::shared_ptr<Bird>(const_cast<Bird*>(this));

	//auto it = Tree::instance().birdPositions.find(a);

	//if (it != Tree::instance().birdPositions.end())
	//{
	//	return it->second;
	//}
	//else 
	//{
	//	return nullptr;
	//}
//}

void Bird::dieOfOldAge()
{
	if (age_ > lifeExpectancy_)
	{
		markedForDeath_ = true;
	}
}