# CSC584 HW3 README

## Build the project

1. Configure and build the project.
   Using CMake from the command line is straightforward as well.
   Run these commands in the HW3 folder of the project.

   ```bash
   cmake -S . -B build
   cmake --build build
   cd ./build/bin/
   ./graph_analysis # run this command to run the graph analysis
   ./sfml_demo # run this command to run the demo integrating pathfinding into HW2
   ```

or run the `./compile_and_test.sh` script from the project root directory.
---

If the cmake doesn't work then try using the Makefile generated for the standard testing environment:

```bash
cd cmake-build/
make clean
make
make run
```

# Run Project
From the `build/bin/` directory, run the following commands to execute the programs:
```bash
./graph_analysis
./sfml_demo
```

## Graph Analysis
This program demonstrates parts 1,2, and 3 of the assignment.

## SFML Demo
This program demonstrates part 4 of the assignment.