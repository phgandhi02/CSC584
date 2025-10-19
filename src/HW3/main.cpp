// SFML libs
#include <SFML/Graphics.hpp>

// STL
#include <memory>
#include <iostream>
#include <random>

int main()
{
    // Seed the random number generator before using random numbers.
    srand(static_cast<unsigned>(time(0)));

    // create window object to render game.
    auto window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "CSC584 HW2: Steering Behaviors");
    window.setFramerateLimit(144); // set the framerate limit to 144 fps.

    // create a texture object to load the boid image.
    sf::Texture texture;
    if (!texture.loadFromFile("assets/boid-sm.png")) // make sure the texture loads correctly.
        return EXIT_FAILURE;

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

            window.display(); // display the new frame.
        }
    }
}