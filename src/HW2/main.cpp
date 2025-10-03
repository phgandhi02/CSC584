#include <SFML/Graphics.hpp>
#include "./include/boid.hpp"
#include "./include/boids_algorithm.hpp"

#include <memory>
#include <iostream>
#include <random>

int main()
{
    srand (static_cast <unsigned> (time(0))); // Seed the random number generator before using random numbers.
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CSC584 HW2: Steering Behaviors"); // create window object to render game.
    window.setFramerateLimit(144); // set the framerate limit to 144 fps.

    sf::Texture texture; // create a texture object to load the boid image.
    if (!texture.loadFromFile("./assets/boid-sm.png")) // make sure the texture loads correctly.
        return EXIT_FAILURE;
    sf::Sprite sprite(texture); // create a sprite object to represent the boid in the window.

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent()) // event polling loop.
        {
            if (event->is<sf::Event::Closed>()) // If user closes the window, close the application.
            {
                window.close();
            }
        }

        window.clear(sf::Color::White); // clear the window with a white background.
        window.display(); // display the new frame.
    }
}
