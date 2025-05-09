#include <algorithm>
#include "Tree.h"

// Main simulation loop that updates all entities and handles tree growth
void Tree::simLoop()
{
	// Calculate growth per branch if root exists
	if (root_) {
		branchGrowthPerTurn = treeGrowthPerTurn_ / branchAmount();
	}
	// Update all entities in the first pass
	std::for_each(entities_.begin(), entities_.end(), [](std::shared_ptr<Entity>& e) {
		e->update();
	});

	// Perform late updates after all entities have been updated
	std::for_each(entities_.begin(), entities_.end(), [](std::shared_ptr<Entity>& e) {
		e->lateUpdate();
		});

	// Clean up any entities marked for destruction
	destroyElements();
}

// Removes entities marked for death and handles cleanup of related objects
void Tree::destroyElements()
{
	// First collect all branches that need to be destroyed
	std::vector<std::shared_ptr<Branch>> branchesToDestroy;
	for (const auto& entity : entities_) {
		if (auto branch = std::dynamic_pointer_cast<Branch>(entity)) {
			if (branch->markedForDeath_) {
				branchesToDestroy.push_back(branch);
			}
		}
	}

	// Handle branch destruction and bird relocation
	for (const auto& branch : branchesToDestroy) {
		// Make birds move when their branch is destroyed
		for (auto& birdPos : birdPositions) {
			if (birdPos.second == branch) {
				birdPos.first->move();
			}
		}
		// If the root branch is dying, update the root pointer
		if (branch == root_) {
			root_ = nullptr;
		}
	}

	// Remove all entities marked for death from the main entity list
	entities_.erase(std::remove_if(entities_.begin(), entities_.end(),
	[](const std::shared_ptr<Entity>& e) { return e->markedForDeath_; }),
	entities_.end());

	// Clean up bird positions when birds die
	for (auto it = birdPositions.begin(); it != birdPositions.end(); ) {
		if (it->first->markedForDeath_) {
			it = birdPositions.erase(it);
		}
		else {
			++it;
		}
	}
}

// Adds a new entity to the update subscription list
void Tree::subscribeToUpdate(std::shared_ptr<Entity> entity)
{
	entities_.push_back(entity);
	numEntities_++;
}

// Sets the root branch of the tree
void Tree::setRoot(std::shared_ptr<Branch> root)
{
	root_ = root;
}

// Performs a breadth-first traversal of the tree and prints branch information
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

		// Add all children to the queue for processing
		const auto& children = currentNode->children();
		for (const auto& child : children) {
			nodeQueue.push(child);
		}
	}
}

// Counts the total number of branches in the tree
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

		// Add all children to the queue for counting
		const auto& children = currentNode->children();
		for (const auto& child : children) {
			nodeQueue.push(child);
		}
	}
	return count;
}

// Finds the branch with the highest life value in the tree
std::shared_ptr<Branch> Tree::getLiveliestBranch()
{
	if (!root_) {
		return 0; // Empty tree, nothing to traverse
	}

	double maxLife = 0;
	std::shared_ptr<Branch> bestBranch;

	std::queue<std::shared_ptr<Branch>> nodeQueue;
	nodeQueue.push(root_);

	while (!nodeQueue.empty()) {
		const std::shared_ptr<Branch> currentNode = nodeQueue.front();
		nodeQueue.pop();

		// Update best branch if current branch has more life
		if (currentNode->life() > maxLife)
		{
			bestBranch = currentNode;
			maxLife = currentNode->life();
		}

		// Add all children to the queue for checking
		const auto& children = currentNode->children();
		for (const auto& child : children) {
			nodeQueue.push(child);
		}
	}
	return bestBranch;
}