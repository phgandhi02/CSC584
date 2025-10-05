#include <SFML/Graphics.hpp>
#include "./include/boid.hpp"
#include "./include/boids_algorithm.hpp"

#include <memory>
#include <iostream>
#include <random>

int main()
{
    // Seed the random number generator before using random numbers.
    srand(static_cast<unsigned>(time(0)));

    // create window object to render game.
    auto window = sf::RenderWindow(sf::VideoMode({800, 600}), "CSC584 HW2: Steering Behaviors");
    window.setFramerateLimit(144); // set the framerate limit to 144 fps.

    // create a texture object to load the boid image.
    sf::Texture texture;
    if (!texture.loadFromFile("assets/boid-sm.png")) // make sure the texture loads correctly.
        return EXIT_FAILURE;
    // sf::Sprite sprite(texture); // create a sprite object to represent the boid in the window.
    Static startPos = Static(sf::Vector2f(400, 300), sf::degrees(0.0f));
    // auto seek_behavior = KinematicSeek();
    Boid boid(texture, startPos, window);
    auto seek_behavior = std::make_unique<KinematicSeek>();
    boid.m_controller = std::move(seek_behavior);

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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::I))
            {
                boid.speed *= 1.01f;
            } 
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::M))
            {
                boid.speed *= 0.99f;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::O))
            {
                boid.smoothing *= 1.01f;
            } 
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::U))
            {
                boid.smoothing *= 0.99f;
            }


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Q))
            {
                boid.m_controller = std::move(std::make_unique<KinematicAlign>());
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
            {
                boid.m_controller = std::move(std::make_unique<KinematicArrive>(5.0f));
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::E))
            {
                boid.m_controller = std::move(std::make_unique<KinematicFlee>());
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::R))
            {
                boid.m_controller = std::move(std::make_unique<KinematicSeek>());
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::T))
            {
                boid.m_controller = std::move(std::make_unique<KinematicWander>());
            }
        }

        boid.update(0.01f);
        boid.draw(window);

        window.display(); // display the new frame.
    }
}
