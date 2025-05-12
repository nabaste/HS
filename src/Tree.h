#pragma once
#include <list>
//#include <algorithm>
#include <map>

#include "Entity.h"
#include "Branch.h"
#include "Bird.h"

class Tree {
public:
	// Constants for tree mechanics
	static constexpr double TREE_GROWTH_PER_TURN = 10.00;
	static constexpr double INITIAL_BRANCH_GROWTH_PER_TURN = 0.00;

	static Tree& instance()
	{
		static Tree instance;
		return instance;
	}

	// Delete the copy constructor and copy assignment operator to ensure no copy of the instance can be created
	Tree(const Tree&) = delete;
	Tree& operator=(const Tree&) = delete;
	
	void simLoop();
	void subscribeToUpdate(std::shared_ptr<Entity> entity);
	void destroyElements();

	void setRoot(std::shared_ptr<Branch> root);
	void breadthFirstTraversal() const;
	int branchAmount() const;
	std::shared_ptr<Branch> getLiveliestBranch() const;
	
	double branchGrowthPerTurn;

	std::map<std::shared_ptr<Bird>, std::shared_ptr<Branch>> birdPositions;

private:
	Tree() {
		numEntities_ = 0;
		root_ = nullptr;
		treeGrowthPerTurn_ = TREE_GROWTH_PER_TURN;
		branchGrowthPerTurn = INITIAL_BRANCH_GROWTH_PER_TURN;
	};

	std::list<std::shared_ptr<Entity>> entities_;
	int numEntities_;

	std::shared_ptr<Branch> root_;
	double treeGrowthPerTurn_;
};