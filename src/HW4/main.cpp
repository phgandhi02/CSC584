// Global Include 
#include "./include/global.hpp"

// Repo Lib includes
#include "movement/boid.hpp" // boid object which handles inputs events and steering behavior
#include "pathfinding/graph.hpp" // graph object for graph representation of world for pathfinding
#include "pathfinding/pathfinding_algos.hpp" // algorithms for pathfinding (Dijkstra's and A*)

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

    // create game objects and game state vars

    // window creates Window obj. Must include event handling loop to ensure
    // the program doesn't end immediately. 
    // * use sf::VideoMode to get desktop resolution for dynamic sizing
    sf::RenderWindow window(sf::VideoMode({800, 600}), "CSC584 HW4"); 

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
        
        // * Must call clear before drawing anything o.w. content from previous frames will show.
        window.clear(sf::Color::White);

        // draw on window

        // * must call display end the current frame
        window.display();
    }
}