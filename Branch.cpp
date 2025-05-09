#include "Tree.h"

void Branch::update()
{
    grow();
    if (life_ > SPAWN_CHILD_THRESHOLD)
    {
        this->spawnChild();
        life_ = LIFE_AFTER_SPAWN;
    }
}

void Branch::lateUpdate()
{
    if (life_ <= 0)
    {
        // First notify parent to remove this branch from its children
        if (parent_) {
            parent_->looseChildren(data_);
        }
        // Then handle the branch's own death and falling
        die();
        fallDown();
    }
}

void Branch::grow()
{
    life_ += Tree::instance().branchGrowthPerTurn;
}

void Branch::addChild(std::shared_ptr<Branch> child)
{
    children_.push_back(child);
    child->setParent(shared_from_this());
}

void Branch::setParent(std::shared_ptr<Branch> parent)
{
    parent_ = parent;
}

void Branch::looseChildren(int data)
{
    if (data == 1) return; //root
    children_.erase(std::remove_if(children_.begin(), children_.end(),
        [data](const std::shared_ptr<Branch>& e) { return e->data() == data; }),
        children_.end());
}

void Branch::looseLife(double amount)
{
    life_ = std::max(0.0, life_ - amount);
}

void Branch::spawnChild()
{
    int count = Tree::instance().branchAmount();
    std::shared_ptr<Branch> newBranchPtr = std::make_shared<Branch>(count+1);
    
    Tree::instance().subscribeToUpdate(newBranchPtr);
    this->addChild(newBranchPtr);
}

void Branch::fallDown()
{
    if (children_.empty()) {
        // There are no children
        return;
    }

    std::cout << "Branch " << data_ << " has fallen" << std::endl;

    std::queue<std::shared_ptr<Branch>> nodeQueue;
    // Add all children to the queue initially
    for (const auto& child : children_) {
        if (child) {
            nodeQueue.push(child);
        }
    }

    while (!nodeQueue.empty()) {
        const std::shared_ptr<Branch> currentNode = nodeQueue.front();
        nodeQueue.pop();

        if (currentNode) {
            currentNode->looseLife(FALL_DAMAGE);

            const auto& children = currentNode->children();
            for (const auto& child : children) {
                if (child) {
                    nodeQueue.push(child);
                }
            }
        }
    }
}

void Branch::die()
{
    markedForDeath_ = true;
}
