#include <SFML/Graphics.hpp>
#include "./include/boid.hpp"
#include "./include/boids_algorithm.hpp"

#include <memory>
#include <iostream>
#include <random>

int main()
{
    // Seed the random number generator before using random numbers.
    srand (static_cast <unsigned> (time(0)));
    
    // create window object to render game.
    auto window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "CSC584 HW2: Steering Behaviors"); 
    window.setFramerateLimit(144); // set the framerate limit to 144 fps.

    // create a texture object to load the boid image.
    sf::Texture texture; 
    if (!texture.loadFromFile("./assets/boid-sm.png")) // make sure the texture loads correctly.
        return EXIT_FAILURE;
    sf::Sprite sprite(texture); // create a sprite object to represent the boid in the window.

    // auto seek_behavior = KinematicSeek();
    Boid boid(texture, 250.f, sf::Vector2f());
    auto align_behavior = std::make_unique<KinematicAlign>();
    boid.m_controller = std::move(align_behavior);

    // Game Loop
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent()) // event polling loop.
        {
            if (event->is<sf::Event::Closed>()) // If user closes the window, close the application.
            {
                window.close();
            }
        }

        boid.update(0.01f);

        window.clear(sf::Color::White); // clear the window with a white background.
        window.display(); // display the new frame.
    }
}
