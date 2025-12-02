#include "./include/global.hpp"
#include "./include/pathfinding/graph.hpp"
#include "./include/pathfinding/pathfinding_algos.hpp"

// Boid libs
#include "./include/movement/boid.hpp"

// SFML libs
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

// STL
#include <iostream>
#include <memory>
#include <random>

int main() {
    /* -------------------------------------------------------------------------- */
    /*                               Game Loop Setup                              */
    /* -------------------------------------------------------------------------- */

    // window creates Window obj. Must include event handling loop to ensure
    // the program doesn't end immediately. 
    // * use sf::VideoMode to get desktop resolution for dynamic sizing
    sf::Window window(sf::VideoMode({800, 600}), "CSC584 HW4"); 

    /* -------------------------------------------------------------------------- */
    /*                               Main Game Loop                               */
    /* -------------------------------------------------------------------------- */
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last
        // iteration of the loop
        while (const std::optional event = window.pollEvent()) {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                // Implement any logic needed before closing game ie. save game etc.
                window.close();
            
            /* ------------------------- Check for Input Events ------------------------- */
        }
    }
}