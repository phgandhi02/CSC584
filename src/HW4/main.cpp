/*
TODO: add kitchen asset sprites to map

TODO: implement seed eating behavior

TODO: implement movement behaviors for enemy
TODO: implement pathfinding behaviors for enemy
TODO: implement decision tree for enemy
*/
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
void draw_map(std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> map, sf::RenderWindow &window)
{
    auto FLOOR_BROWN = sf::Color(210,180,140);
    auto WALL_DARK_BROWN = sf::Color(139,69,19);

    auto cell_shape = sf::RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    for (unsigned int i = 0; i < MAP_HEIGHT; i++)
    {
        for (unsigned int j = 0; j < MAP_WIDTH; j++)
        {
            // indicies are switched because of SFML x-y direction convention
            cell_shape.setPosition(sf::Vector2f(static_cast<float>(CELL_SIZE * j), static_cast<float>(CELL_SIZE * i)));

            // map prints sideways so indices are switched.
            switch (map[i][j])
            {
            case Cell::Wall:
                cell_shape.setFillColor(WALL_DARK_BROWN);
                break;

            default:
                cell_shape.setFillColor(FLOOR_BROWN);
                break;
            }
            window.draw(cell_shape);
        }
    }
};

std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> generate_scene()
{
    // convert MAP_SKETCH into map
    std::array<std::string, MAP_HEIGHT> MAP_SKETCH = {
    "########################################",
    "#           #                          #",
    "#           #                          #",
    "#           #                          #",
    "#           #                          #",
    "#           #                          #",
    "#           #                          #",
    "#####   ###################   ##########",
    "#                  #                   #",
    "#                  #                   #",
    "#                  #                   #",
    "#                  #                   #",
    "#                  #                   #",
    "#                                      #",
    "#                                      #",
    "#                                      #",
    "#                  #                   #",
    "#                  #                   #",
    "#                  #                   #",
    "#                  #                   #",
    "#                  #                   #",
    "#                  #                   #",
    "########   ###################   #######",
    "#                         #            #",
    "#                         #            #",
    "#                         #            #",
    "#                         #            #",
    "#                         #            #",
    "#                         #            #",
    "#                         #            #",
    "#                         #            #",
    "#                         #            #",
    "###################   ##################",
    "#                                      #",
    "#                                      #",
    "#                                      #",
    "#########                              #",
    "#                                      #",
    "#                                      #",
    "########################################"};
    std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> map = convert_sketch_to_map(MAP_SKETCH);
    return map;
}

int main() {
    /* -------------------------------------------------------------------------- */
    /*                               Game Loop Setup                              */
    /* -------------------------------------------------------------------------- */
    auto rng = RandomNumGen(40,760); // Create random number generator for getting random seed locations

    // window creates Window obj. Must include event handling loop to ensure the program doesn't end immediately. 
    // * use sf::VideoMode to get desktop resolution for dynamic sizing
    sf::RenderWindow window(sf::VideoMode({800, 800}), "CSC584 HW4"); 
    window.setFramerateLimit(60); // set the framerate limit to 60 fps.

    /* ------------------------------- Setup graph ------------------------------ */
    auto map = generate_scene();
    Graph graph = Graph();
    std::cout << "Generating a graph!" << std::endl;
    auto edges = GenMapGraph(map);
    for (Connection &edge : edges)
    {
        graph.addEdge(edge);
    }

    /* ---------------------------- Setup Pathfinding --------------------------- */
    auto pathfinding = Pathfinding();
    std::vector<Connection> path;
    // stores the node value for start, current, mouse input, and the next target.
    unsigned int startNode, currentNode, targetNode, goalNode;

    int i = 0;
    auto seedTexture = sf::Texture("seeds.png");
    sf::Sprite seed(seedTexture);
    seed.scale(sf::Vector2f(.3,.3));

    // Create enemy sprite
    auto enemyCatTexture = sf::Texture("chasingCat.png");
    auto enemyStartPos = Static(sf::Vector2f(100,100), sf::degrees(0));
    Boid enemyCat(enemyCatTexture, enemyStartPos, window);
    enemyCat.setSpriteScale(.3,.3);
    enemyCat.mouseInputOn = true;
    auto seek_behavior = std::make_unique<KinematicSeek>();
    enemyCat.controller = std::move(seek_behavior);
    enemyCat.breadcrumbs_on = false;
    /* -------------------------------------------------------------------------- */
    /*                               Main Game Loop                               */
    /* -------------------------------------------------------------------------- */
    while (window.isOpen()) 
    {
        // check all the window's events that were triggered since the last
        // iteration of the loop
        while (const std::optional event = window.pollEvent()) 
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
            {
                // Implement any logic needed before closing game ie. save game etc.
                window.close();
            
            /* ------------------------- Check for Input Events ------------------------- */
            }
        }

        // * Must call clear before drawing anything o.w. content from previous frames will show.
        window.clear(sf::Color::White);

        // draw on window
        draw_map(map, window); // draw map
        enemyCat.update(0.01f);
        enemyCat.draw(window);

        i++;
        if ((i % 100) == 0)
        {
            auto random_position = sf::Vector2f();
            while (path.empty())
            {
                random_position = sf::Vector2f(rng.getRandomInt(),rng.getRandomInt());
                startNode = 42;
                goalNode = calculateNodeIndex(random_position);
                EuclidianHeuristic heuristic;
                path = pathfinding.Astar(graph, startNode, goalNode, heuristic);
                std::cout << random_position.x << " | " << random_position.y << std::endl;      
            }    

            seed.setPosition(random_position);
            window.draw(seed);
            i = 0;
            path = std::vector<Connection>();
        } else {
            window.draw(seed);
        }


        // * must call display end the current frame
        window.display();
    }
}