#include "Tree.h";

void Branch::update()
{
    grow();
    if (life_ > 25.00)
    {
        this->spawnChild();
        life_ = 15.00;
    }
}

void Branch::lateUpdate()
{

}

void Branch::grow()
{
    life_ += Tree::instance().branchGrowthPerTurn;
}

void Branch::looseLife(double amount)
{
    life_ -= amount;
}

void Branch::spawnChild()
{
    int count = Tree::instance().branchAmount();
    std::shared_ptr<Branch> newBranchPtr = std::make_shared<Branch>(count+1);
    
    Tree::instance().subscribeToUpdate(newBranchPtr);
    this->addChild(newBranchPtr);

}