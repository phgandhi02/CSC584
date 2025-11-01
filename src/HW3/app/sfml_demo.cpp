#include "../include/graph.hpp"
#include "../include/pathfinding_algos.hpp"

// Boid libs
#include "../include/movement/boid.hpp"
#include "../include/movement/boids_colony.hpp"

// Steering behavior libs
#include "../include/movement/steering/kinematic_align.hpp"
#include "../include/movement/steering/kinematic_arrive.hpp"
#include "../include/movement/steering/kinematic_flee.hpp"
#include "../include/movement/steering/kinematic_seek.hpp"
#include "../include/movement/steering/kinematic_wander.hpp"
#include "../include/movement/delegated_steering/kinematic_face.hpp"
#include "../include/movement/delegated_steering/wander.hpp"

// SFML libs
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

// STL
#include <memory>
#include <iostream>
#include <random>

int main()
{
    // Seed the random number generator before using random numbers.
    srand(static_cast<unsigned>(time(0)));
    bool boidsColonyOn = true;
    // create window object to render game.
    auto window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "CSC584 HW2: Steering Behaviors");
    window.setFramerateLimit(144); // set the framerate limit to 144 fps.

    // create a texture object to load the boid image.
    sf::Texture texture;
    if (!texture.loadFromFile("/home/prem/code/CSC584/src/HW3/assets/boid-sm.png")) // make sure the texture loads correctly.
        return EXIT_FAILURE;
    // sf::Sprite sprite(texture); // create a sprite object to represent the boid in the window.
    Static startPos = Static(sf::Vector2f(400, 300), sf::degrees(0.0f));

    Boid boid(texture, startPos, window);
    boid.mouseInputOff = false;
    auto seek_behavior = std::make_unique<KinematicSeek>();
    boid.controller = std::move(seek_behavior);

    auto boidsColony = BoidsColony(texture, window, 10.0f, 0.4f, 0.1f, 200);

    // Game Loop
    while (window.isOpen())
    {
        window.clear(sf::Color::White);                        // clear the window with a white background.
        while (const std::optional event = window.pollEvent()) // event polling loop.
        {
            if (event->is<sf::Event::Closed>()) // If user closes the window, close the application.
            {
                window.close();
            }

            if (event->getIf<sf::Event::KeyPressed>())
            {
                if (event->getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scancode::B)
                {
                    boidsColonyOn = !boidsColonyOn;
                    boidsColonyOn ? std::cout << "Boids Colony Toggled On" << std::endl : std::cout << "Boids Colony Toggled Off" << std::endl;
                    boidsColonyOn ? boid.mouseInputOff = true : boid.mouseInputOff = false;
                }
            }

            if (!boidsColonyOn)
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
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
                {
                    boid.controller = std::move(std::make_unique<KinematicArrive>(5.0f));
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::E))
                {
                    boid.controller = std::move(std::make_unique<KinematicFlee>());
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::R))
                {
                    boid.controller = std::move(std::make_unique<KinematicSeek>());
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::T))
                {
                    boid.controller = std::move(std::make_unique<KinematicWander>());
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::F))
                {
                    boid.controller = std::move(std::make_unique<KinematicFace>());
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
                {
                    boid.controller = std::move(std::make_unique<Wander>(window.getSize().x, window.getSize().y));
                }
            }
        }
        if (!boidsColonyOn)
        {
            boid.update(0.01f);
            boid.draw(window);
        }
        if (boidsColonyOn)
        {
            boidsColony.update();
            boidsColony.draw(window);
        }

        window.display(); // display the new frame.
    }
}
