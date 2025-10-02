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

    // Construct the boid sprites and pass the boid object as a unique_ptr to the vector to store the collection. 
    // std::vector<std::unique_ptr<Boid>> boids;
    // for (int i = 0; i < 50; i++){
    //     boids.push_back(std::make_unique<Boid>()); // append the boid to the boids vector as a unique_ptr to ensure memory is shared efficiently.
    // }
    // Create the Boids Algorithm object to control the movement behavior for the boids in an easy interface. 
    // BoidsAlgorithm boids_algorithm = BoidsAlgorithm(boids,1.0f,1.0f,1.0f); 
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent()) // event polling loop.
        {
            if (event->is<sf::Event::Closed>()) // If user closes the window, close the application.
            {
                window.close();
            }
        }

        // for (auto& boidPtr: boids){
        //     // Update the boids states using the existing boids algorithm params.
        //     boids_algorithm.update();
        // }

        window.clear(sf::Color::White); // clear the window with a white background.
        window.display(); // display the new frame.
    }
}
