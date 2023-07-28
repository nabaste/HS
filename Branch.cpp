#include "Branch.h"
#include"Entity.h"
#include "Tree.h";

void Branch::update()
{
    grow();
}

void Branch::grow()
{
    life_ += Tree::instance().branchGrowthPerTurn;
}

void Branch::looseLife(double amount)
{
    life_ -= amount;
}