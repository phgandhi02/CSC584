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
        boid.update(0.01f);
        boid.draw(window);

        window.display(); // display the new frame.
    }
}
