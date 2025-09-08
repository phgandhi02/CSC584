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


// int main()
// {
//     float spriteSpeed = 0.5f;
//     float* spriteSpeedPtr = &spriteSpeed;
//     bool spriteStopped = false; // false = moving, true = stopped 
    
//     std::cout << "Sprite speed: " << *spriteSpeedPtr << std::endl; // AI generated

//     // Create the main window
//     sf::RenderWindow window(sf::VideoMode(640, 480), "SFML window");
//     // Load a sprite to display
//     sf::Texture texture;
//     if (!texture.loadFromFile("/home/prem/CSC584/HW1/src/boid-sm.png"))
//         return EXIT_FAILURE;
//     sf::Sprite sprite(texture);
//     // Create a graphical text to display
//     sf::Font font;
//     if (!font.loadFromFile("arial.ttf"))
//         return EXIT_FAILURE;
//     sf::Text text("Hello SFML", font, 50);
//     // Load a music to play
//     // sf::Music music;
//     // if (!music.openFromFile("file_example_OOG_1MG.ogg"))
//     //     return EXIT_FAILURE;
//     // // Play the music
//     // music.play();
//     // Start the game loop

//     sf::CircleShape shape(100.f);
//     shape.setFillColor(sf::Color::Green);

//     while (window.isOpen())
//     {
//         // Process events
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             // Close window: exit
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }
//         // Clear screen
//         window.clear(sf::Color::White);
        
//         // Draw the string
//         window.draw(text);
//         // Draw the shape
//         // window.draw(shape);
//         // Update the window

//         // If in top left corner, move right
//         if (sprite.getPosition().x >= 0 and sprite.getPosition().y <= 0){
//             sprite.move(sf::Vector2f(*spriteSpeedPtr, 0.f));
//             // Draw the sprite
//             window.draw(sprite);
//         }
//         // If in top right corner, rotate 90 degrees and move down
//         if (sprite.getPosition().x >= 640 and sprite.getPosition().y >= 0){
//             // Rotate 90 degrees if not already rotated like when first reaching this corner
//             if (sprite.getRotation() != 90.f){
//                 sprite.setRotation(90.f);
//             }
//             sprite.move(sf::Vector2f(0.f, *spriteSpeedPtr));
//             // Draw the sprite
//             window.draw(sprite);
//         }
//         if (sprite.getPosition().x >= 0 and sprite.getPosition().y >= 480){
//             // Rotate 90 degrees if not already rotated like when first reaching this corner
//             if (sprite.getRotation() != 180.f){
//                 sprite.setRotation(180.f);
//             }
//             sprite.move(sf::Vector2f(-1.0f * *spriteSpeedPtr, 0.f));
//             // Draw the sprite
//             window.draw(sprite);
//         }
//         if (sprite.getPosition().x <= 0 and sprite.getPosition().y >= 0 and spriteStopped == false){
//             // Rotate 90 degrees if not already rotated like when first reaching this corner
//             if (sprite.getRotation() != 270.f){
//                 sprite.setRotation(270.f);
//             }
//             // if (sprite.getPosition().y <= 0){
//             //     sprite.setRotation(0.f);
//             // }
//             if (sprite.getPosition().y <= 0){
//                 spriteStopped = true;
//                 std::cout << "Sprite Stopped" << std::endl;
//             }

//             if (spriteStopped != true){
//                 sprite.move(sf::Vector2f(0.f, -1.0f * *spriteSpeedPtr));
//                 // Draw the sprite
//                 window.draw(sprite);
//             }
//         }

//         // std::cout << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl; // AI generated
//         window.display();
//     }
//     return EXIT_SUCCESS;
// }