#include <iostream>
#include <chrono>
#include "Tree.h"

void render(int turnNumber)
{
	std::cout << "It is turn number "<< turnNumber << "\n" << "There are " << Tree::instance().branchAmount() << " branches: " << std::endl;
	Tree::instance().breadthFirstTraversal();
	std::cout << "There are " << Tree::instance().birdPositions.size() << " birds:" << std::endl;
	for (std::pair<std::shared_ptr<Bird>, std::shared_ptr<Branch>> kv : Tree::instance().birdPositions)
	{
		std::cout << "	Bird no. " << kv.first->name() << " is " << kv.first->age() << " turns old and is on branch " << kv.second->data() << " with life " << kv.first->life() << std::endl;
	}
	std::cout << "\n" << std::endl;
}

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);


	Tree& tree = Tree::instance();
	std::shared_ptr<Branch> rootPtr = std::make_shared<Branch>(1);
	tree.setRoot(rootPtr);
	tree.subscribeToUpdate(rootPtr);

	std::shared_ptr<Branch> branch2Ptr = std::make_shared<Branch>(2);
	std::shared_ptr<Branch> branch3Ptr = std::make_shared<Branch>(3);

	tree.subscribeToUpdate(branch2Ptr);
	tree.subscribeToUpdate(branch3Ptr);


	rootPtr->addChild(branch2Ptr);
	rootPtr->addChild(branch3Ptr);
	
	std::shared_ptr<Bird> birdAPtr = std::make_shared<Bird>(1);
	std::shared_ptr<Bird> birdBPtr = std::make_shared<Bird>(2);

	tree.subscribeToUpdate(birdAPtr);
	tree.subscribeToUpdate(birdBPtr);
	
	tree.birdPositions[birdAPtr] = branch2Ptr;
	tree.birdPositions[birdBPtr] = branch2Ptr;
	
	render(-1);
	//GAME LOOP
	int turnNo = 0;
	double MS_PER_UPDATE = 1.60;
	auto previous = std::chrono::high_resolution_clock::now();
	double lag = 0.0;
	while (true)
	{
		auto current = std::chrono::high_resolution_clock::now();
		auto elapsed = current - previous;
		previous = current;
		lag += std::chrono::duration<double>(elapsed).count();

		//processInput();

		while (lag >= MS_PER_UPDATE)
		{
			tree.simLoop();
			lag -= MS_PER_UPDATE;
			render(turnNo);
			turnNo++;
		}

	}

}
