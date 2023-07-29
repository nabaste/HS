#pragma once
#include <list>
//#include <algorithm>
#include <map>

#include "Entity.h"
#include "Branch.h"
#include "Bird.h"

class Tree {
public:
	static Tree& instance()
	{
		static Tree* instance = new Tree();
		return *instance;
	}

	// Delete the copy constructor and copy assignment operator to ensure no copy of the instance can be created
	Tree(const Tree&) = delete;
	Tree& operator=(const Tree&) = delete;
	
	void simLoop();
	void subscribeToUpdate(std::shared_ptr<Entity> entity);

	void setRoot(std::shared_ptr<Branch> root);
	void const breadthFirstTraversal();
	int const branchAmount();
	
	double branchGrowthPerTurn;

	std::map<std::shared_ptr<Bird>, std::shared_ptr<Branch>> birdPositions;

private:
	Tree() {
		numEntities_ = 0;
		root_ = nullptr;
		treeGrowthPerTurn_ = 10.00;
		branchGrowthPerTurn = 0;
	};

	std::list<std::shared_ptr<Entity>> entities_;
	int numEntities_;

	std::shared_ptr<Branch> root_;
	double treeGrowthPerTurn_;
};