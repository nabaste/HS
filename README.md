# Tree and Bird Ecosystem Simulation

This project implements a simulation of a dynamic ecosystem where birds interact with a growing tree structure. The simulation models the life cycle of birds, their interactions with tree branches, and the natural growth and decay of the tree system.

## Overview

The simulation creates a living ecosystem where:
- A tree grows and develops branches over time
- Birds live on branches, consuming resources and reproducing
- The system evolves through turns, with each entity (birds and branches) updating their state
- The simulation continues until either all birds perish or all branches die

## Core Components

### Tree System
- Implemented as a singleton to ensure a single tree instance
- Manages branch growth and decay
- Tracks bird positions and branch structure
- Provides methods for breadth-first traversal of the tree structure


### Bird System
- Birds are entities that live on branches
- Each bird has:
  - Life expectancy: 30 turns
  - Initial life: 100.00 units
  - Food consumption: 1.8 units per turn
  - Mating threshold: 115.00 units
  - Minimum branch life requirement: 13.00 units
  - Life growth rate: 5.3 units per turn
  - Post-mating life: 70.00 units

### Branch System
- Branches are the foundation of the tree structure
- They provide resources for birds
- Can grow and decay over time
- Support multiple birds simultaneously

## Simulation Logic

1. **Initialization**
   - Creates a root branch
   - Spawns initial bird population
   - Sets up the tree structure

2. **Main Loop**
   - Runs at a fixed time step (1.60 seconds per update)
   - Each turn:
     - Updates all entities (birds and branches)
     - Birds can:
       - Move between branches
       - Consume resources
       - Reproduce if conditions are met
       - Die of old age
     - Branches can:
       - Grow or decay
       - Support bird life

3. **Termination Conditions**
   - Simulation ends when:
     - All birds have perished
     - All branches have died

## Design Decisions

1. **Singleton Pattern**
   - Tree is implemented as a singleton to ensure a single source of truth
   - Prevents multiple tree instances from conflicting

2. **Entity Component System**
   - Uses inheritance from a base Entity class
   - Allows for consistent update cycles
   - Enables easy addition of new entity types

3. **Smart Pointers**
   - Uses `std::shared_ptr` for memory management
   - Ensures proper cleanup of resources
   - Prevents memory leaks

4. **Observer Pattern**
   - Entities subscribe to updates from the tree
   - Enables decoupled communication between components

## Building and Running

The project is set up as a Visual Studio solution. To build and run:

1. Open `HS.sln` in Visual Studio
2. Build the solution (F7 or Build > Build Solution)
3. Run the program (F5 or Debug > Start Debugging)

