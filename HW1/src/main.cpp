#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include "boid.hpp"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML window");
    // Load a texture for the sprite
    sf::Texture texture;
    if (!texture.loadFromFile("/home/prem/CSC584/HW1/src/boid-sm.png"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);
    
    Boid boid(texture, 0.5f, sf::Vector2f(0.f, 0.f));
    
    // Main game loop
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
    }

    window.clear(sf::Color::White);
    boid.update();
    boid.draw(window);
    window.display();
    
    }
    
    return EXIT_SUCCESS; // AI-generated
}