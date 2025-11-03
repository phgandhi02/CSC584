#include "../include/graph.hpp"
#include "../include/pathfinding_algos.hpp"

// Boid libs
#include "../include/movement/boid.hpp"

// SFML libs
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

// STL
#include <memory>
#include <iostream>
#include <random>

void boid_movement(Boid &boid, sf::Window &window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::I))
    {
        boid.speed *= 1.01f;
        std::cout << "New Speed: " << boid.speed << " | Reset to default with \"K\" key" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::M))
    {
        boid.speed *= 0.99f;
        std::cout << "New Speed: " << boid.speed << " | Reset to default with \"K\" key" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::O))
    {
        boid.smoothing *= 1.01f;
        std::cout << "New Smoothing: " << boid.smoothing << " | Reset to default with \"K\" key" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::U))
    {
        boid.smoothing *= 0.99f;
        std::cout << "New Smoothing: " << boid.smoothing << " | Reset to default with \"K\" key" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::K))
    {
        boid.speed = 100.f;
        boid.smoothing = 0.2f;
        std::cout << "Speed set to default: " << boid.speed << std::endl;
        std::cout << "Smoothing set to default: " << boid.smoothing << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Q))
    {
        boid.controller = std::move(std::make_unique<KinematicAlign>());
        std::cout << "Boid Aligning" << std::endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
    {
        boid.controller = std::move(std::make_unique<KinematicArrive>(5.0f));
        std::cout << "Boid Arriving" << std::endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::E))
    {
        boid.controller = std::move(std::make_unique<KinematicFlee>());
        std::cout << "Boid Fleeing" << std::endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::R))
    {
        boid.controller = std::move(std::make_unique<KinematicSeek>());
        std::cout << "Boid Seeking" << std::endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::T))
    {
        boid.controller = std::move(std::make_unique<KinematicWander>());
        std::cout << "Boid Kinematic Wander" << std::endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::F))
    {
        boid.controller = std::move(std::make_unique<KinematicFace>());
        std::cout << "Boid Kinematic Face" << std::endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
    {
        boid.controller = std::move(std::make_unique<Wander>(window.getSize().x, window.getSize().y));
        std::cout << "Boid Wander" << std::endl;
    }
}

int main()
{
    /* ------------------------------- Setup Boid ------------------------------- */

    std::cout << "Program Running!" << std::endl;
    // Seed the random number generator before using random numbers.
    srand(static_cast<unsigned>(time(0)));
    // create window object to render game.
    auto window = sf::RenderWindow(sf::VideoMode({400u, 400u}), "CSC584 HW2: Steering Behaviors");
    window.setFramerateLimit(144); // set the framerate limit to 144 fps.

    // create a texture object to load the boid image.
    sf::Texture texture;
    if (!texture.loadFromFile("/home/prem/code/CSC584/src/HW3/assets/boid-sm.png")) // make sure the texture loads correctly.
        return EXIT_FAILURE;
    // sf::Sprite sprite(texture); // create a sprite object to represent the boid in the window.
    Static startPos = Static(sf::Vector2f(400, 300), sf::degrees(0.0f));

    Boid boid(texture, startPos, window);
    auto seek_behavior = std::make_unique<KinematicSeek>();
    boid.controller = std::move(seek_behavior);
    boid.mouseInputOff = true;

    /* ------------------------------- Setup graph ------------------------------ */
    // Need to make a graph out of the window.
    Graph graph = Graph();
    std::cout << "Generating a graph!" << std::endl;
    auto edges = GenGridGraph(window.getSize().x / 2, window.getSize().y / 2);

    // std::vector<std::vector<int>> matrix(4, std::vector<int>(4));

    // auto edges = GenGridGraph(4, 4);

    for (Connection &edge : edges)
    {
        graph.addEdge(edge);
    }
    auto pathfinding = Pathfinding();

    auto inputHandler = InputHandler(window);

    int x_pos, y_pos;
    auto prevTarget = inputHandler.update();
    auto target = Static();

    // int startNode = (window.getSize().x / 2) * window.getSize().x + (window.getSize().y / 2);
    int startNode = 100;

    auto path = pathfinding.DijkstraAlgorithm(graph, startNode, prevTarget.getPosition().x * window.getSize().x + prevTarget.getPosition().y);
    x_pos = path.back().getToNode() / window.getSize().y;
    y_pos = path.back().getToNode() % window.getSize().y;
    auto boidWaypoint = Static(sf::Vector2f(x_pos, y_pos), sf::degrees(0));
    boid.setTarget(boidWaypoint);
    /* -------------------------------------------------------------------------- */
    /*                                  Game Loop                                 */
    /* -------------------------------------------------------------------------- */
    while (window.isOpen())
    {
        window.clear(sf::Color::White); // clear the window with a white background.
        target = inputHandler.update();
        if ((prevTarget == target) == false)
        {
            path = pathfinding.DijkstraAlgorithm(graph, 1, target.getPosition().x * window.getSize().x + target.getPosition().y);
        }
        else
        {
            if (static_cast<sf::Vector2i>(boid.getCharacter().getPosition()) == static_cast<sf::Vector2i>(boidWaypoint.getPosition()))
            {
                x_pos = path.back().getToNode() / window.getSize().y;
                y_pos = path.back().getToNode() % window.getSize().y;
                boidWaypoint = Static(sf::Vector2f(x_pos, y_pos), sf::degrees(0));
                boid.setTarget(boidWaypoint);
                path.pop_back();
            }
        }

        while (const std::optional event = window.pollEvent()) // event polling loop.
        {
            if (event->is<sf::Event::Closed>()) // If user closes the window, close the application.
            {
                window.close();
            }

            boid_movement(boid, window);
        }
        boid.update(0.01f);
        boid.draw(window);

        window.display(); // display the new frame.
    }
}
