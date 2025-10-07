# CSC584 HW2 README

## Features (partly generated using ChatGPT)

- Boids Colony Simulation: Watch a colony of boids flock together with adjustable weights for separation, cohesion, and alignment.
- Wander Behavior: When no neighbors are nearby, boids will wander around the screen randomly.
- Individual Steering Mode: Toggle the colony off to control a single boid and test various classic steering behaviors.

## Build the project

1. Configure and build the project.
   Using CMake from the command line is straightforward as well.
   Run these commands in the HW2 folder of the project.

   ```bash
   cmake -S . -B build
   cmake --build build
   ```

1. Run the executable at `./build/bin/main`.

## Interactive Controls (table generated using ChatGPT)

- Set targets for boids by clicking the mouse.  
- Dynamically adjust the boid's speed and rotation smoothing.  
- Switch between different steering algorithms in real time.  

|  Key  | Action                                                   |
| :---: | :------------------------------------------------------- |
| **B** | Toggle between **Boids Colony** and **Single Boid** mode |

| Key / Mouse     | Action                                       |
| :-------------- | :------------------------------------------- |
| **Mouse Click** | Set target for the current steering behavior |
| **I / M**       | Increase / Decrease the boid’s speed         |
| **O / U**       | Increase / Decrease rotation smoothing       |
| **K**           | Reset speed and smoothing to default         |
| **Q**           | Set steering to **Align**                    |
| **W**           | Set steering to **Arrive**                   |
| **E**           | Set steering to **Flee**                     |
| **R**           | Set steering to **Seek**                     |
| **T**           | Set steering to **Kinematic Wander**         |
| **F**           | Set steering to **Face**                     |
| **S**           | Set steering to **Delegated Wander**         |
