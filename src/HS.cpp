#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>
#include "Tree.h"

// Function to display the current state of the simulation
// Shows turn number, branch count, branch traversal, and bird information
// Returns false if simulation should end, true otherwise
bool render(int turnNumber)
{
	// Display current turn number
	std::cout << "It is turn number "<< turnNumber << "\n" << "There are " << Tree::instance().branchAmount() << " branches: " << std::endl;
	// Perform breadth-first traversal of the tree to show branch structure
	Tree::instance().breadthFirstTraversal();
	// Display information about all birds in the simulation
	std::cout << "There are " << Tree::instance().birdPositions.size() << " birds:" << std::endl;
	for (std::pair<std::shared_ptr<Bird>, std::shared_ptr<Branch>> kv : Tree::instance().birdPositions)
	{
		std::cout << "	Bird no. " << kv.first->name() << " is " << kv.first->age() << " turns old and is on branch " << kv.second->data() << " with life " << kv.first->life() << std::endl;
	}
	std::cout << "\n" << std::endl;

	// Check if simulation should end (no birds remaining or no branches left)
	if (Tree::instance().birdPositions.empty() || Tree::instance().branchAmount() == 0) {
		if (Tree::instance().birdPositions.empty()) {
			std::cout << "Simulation over - all birds have perished" << std::endl;
		}
		if (Tree::instance().branchAmount() == 0) {
			std::cout << "Simulation over - all branches have died" << std::endl;
		}
		return false;
	}
	return true;
}

int main()
{

	//if (!glfwInit()) {
	//	std::cerr << "Failed to initialize GLFW\n";
	//	return -1;
	//}

	//GLFWwindow* window = glfwCreateWindow(800, 600, "Hello GLFW", nullptr, nullptr);
	//if (!window) {
	//	std::cerr << "Failed to create GLFW window\n";
	//	glfwTerminate();
	//	return -1;
	//}



	//glfwMakeContextCurrent(window);
	//gladLoadGL(glfwGetProcAddress);

	//while (!glfwWindowShouldClose(window)) {
	//	glClear(GL_COLOR_BUFFER_BIT);

	//	

	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	//}

	//glfwDestroyWindow(window);
	//glfwTerminate();
	//return 0;

	// Enable memory leak detection and debugging
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

	// Get singleton instance of the Tree
	Tree& tree = Tree::instance();
	
	// Create and set up the root branch
	std::shared_ptr<Branch> rootPtr = std::make_shared<Branch>(1);
	tree.setRoot(rootPtr);
	tree.subscribeToUpdate(rootPtr);

	// Create two child branches
	std::shared_ptr<Branch> branch2Ptr = std::make_shared<Branch>(2);
	std::shared_ptr<Branch> branch3Ptr = std::make_shared<Branch>(3);

	// Subscribe the new branches to updates
	tree.subscribeToUpdate(branch2Ptr);
	tree.subscribeToUpdate(branch3Ptr);

	// Add the child branches to the root
	rootPtr->addChild(branch2Ptr);
	rootPtr->addChild(branch3Ptr);
	
	// Create two birds
	std::shared_ptr<Bird> birdAPtr = std::make_shared<Bird>(1);
	std::shared_ptr<Bird> birdBPtr = std::make_shared<Bird>(2);

	// Subscribe the birds to updates
	tree.subscribeToUpdate(birdAPtr);
	tree.subscribeToUpdate(birdBPtr);
	
	// Place both birds on branch 2
	tree.birdPositions[birdAPtr] = branch2Ptr;
	tree.birdPositions[birdBPtr] = branch2Ptr;
	
	// Render initial state (turn -1)
	render(-1);

	// Game loop variables
	int turnNo = 0;
	double MS_PER_UPDATE = 1.60;  // Target time between updates in seconds
	auto previous = std::chrono::high_resolution_clock::now();
	double lag = 0.0;  // Accumulated time since last update
	bool isPlaying = true;  // Control flag for the main game loop

	// Main simulation loop
	while (isPlaying)
	{
		// Calculate elapsed time since last frame
		auto current = std::chrono::high_resolution_clock::now();
		auto elapsed = current - previous;
		previous = current;
		lag += std::chrono::duration<double>(elapsed).count();

		// Process any pending updates based on accumulated time
		while (lag >= MS_PER_UPDATE)
		{
			tree.simLoop();  // Run one simulation step
			lag -= MS_PER_UPDATE;
			isPlaying = render(turnNo);  // Update isPlaying based on render's return value
			turnNo++;
		}
	}
}
