#include "Tree.h"

void Tree::simLoop()
{
	if (root_) {
		branchGrowthPerTurn = treeGrowthPerTurn_ / branchAmount();
	}
	std::for_each(entities_.begin(), entities_.end(), [](std::shared_ptr<Entity>& e) {
		e->update();
	});

	std::for_each(entities_.begin(), entities_.end(), [](std::shared_ptr<Entity>& e) {
		e->lateUpdate();
		});

	destroyElements();
}

void Tree::destroyElements()
{
	entities_.erase(std::remove_if(entities_.begin(), entities_.end(),
	[](const std::shared_ptr<Entity>& e) { return e->markedForDeath_; }),
	entities_.end());

	for (auto it = birdPositions.begin(); it != birdPositions.end(); ) {
		if (it->first->markedForDeath_) {
			it = birdPositions.erase(it);
		}
		else {
			++it;
		}
	}
}

void Tree::subscribeToUpdate(std::shared_ptr<Entity> entity)
{
	entities_.push_back(entity);
	numEntities_++;
}

void Tree::setRoot(std::shared_ptr<Branch> root)
{
	root_ = root;
}

const void Tree::breadthFirstTraversal() {
	if (!root_) {
		std::cout << "Root is nullptr" << std::endl;
		return; // Empty tree, nothing to traverse
	}

	std::queue<std::shared_ptr<Branch>> nodeQueue;
	nodeQueue.push(root_);

	while (!nodeQueue.empty()) {
		const std::shared_ptr<Branch> currentNode = nodeQueue.front();
		nodeQueue.pop();

		std::cout << "	branch " << currentNode->data() << " has " << currentNode->life() << " life." << std::endl;

		const auto& children = currentNode->children();
		for (const auto& child : children) {
			nodeQueue.push(child);
		}
	}
}

const int Tree::branchAmount()
{
	if (!root_) {
		return 0; // Empty tree, nothing to traverse
	}
	int count = 0;

	std::queue<std::shared_ptr<Branch>> nodeQueue;
	nodeQueue.push(root_);

	while (!nodeQueue.empty()) {
		const std::shared_ptr<Branch> currentNode = nodeQueue.front();
		nodeQueue.pop();

		count++;

		const auto& children = currentNode->children();
		for (const auto& child : children) {
			nodeQueue.push(child);
		}
	}
	return count;
}