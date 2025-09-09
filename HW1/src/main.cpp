//  Used Gemini to guide my thinking and understand C++ Syntax.
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include "boid.hpp"

int main()
{
    float SPRITE_SPEED = 0.5f;
    int last_boid_prev_state;
    int last_boid_curr_state;
    int boid_count = 0;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML window");
    // Load a texture for the sprite
    sf::Texture texture;
    if (!texture.loadFromFile("./boid-sm.png"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);
    
    std::array<Boid,4> boids = {{
        Boid(texture, SPRITE_SPEED, sf::Vector2f(0.f, 0.f)),
        Boid(texture, SPRITE_SPEED, sf::Vector2f(0.f, 0.f)),
        Boid(texture, SPRITE_SPEED, sf::Vector2f(0.f, 0.f)),
        Boid(texture, SPRITE_SPEED, sf::Vector2f(0.f, 0.f))
    }};
    boids[0].start();  
    // boid_count++;
    last_boid_prev_state = boids[0].getSpriteState();

    // Main game loop
    while (window.isOpen()){
        last_boid_curr_state = boids[0].getSpriteState();
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        // std::cout << last_boid_curr_state << " | " << last_boid_prev_state << std::endl; // AI generated
        // AI generated
        if (last_boid_curr_state != last_boid_prev_state){
            if (boid_count < 3){
                boid_count++;
                boids[boid_count].start();
            }
        }
        // AI generated

        for (int i = 0; i <= boid_count; i++){
            boids[i].update();
            boids[i].draw(window);
        }
        window.display();

        last_boid_prev_state = last_boid_curr_state;
    }
    
    return EXIT_SUCCESS; // AI-generated
}