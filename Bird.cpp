#include "Bird.h"
#include "Tree.h"

void Bird::update()
{
	eat();
	grow();
}

void Bird::eat()
{
	//std::map<std::shared_ptr<Bird>, std::shared_ptr<Branch>>& birdPos = Tree::instance().birdPositions;
	//std::for_each(birdPos.begin(), birdPos.end(), [this](auto& p) {
	//	auto& [key, value] = p;
	//	if (key.get() == this) {
	//		value->looseLife(foodConsumedPerTurn_);
	//	}
	//	});
}

void Bird::grow()
{
	life_ += 1.3;
	age_++;
 }

void Bird::mate()
{

}

void Bird::move()
{

}
