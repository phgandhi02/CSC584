#include <SFML/Graphics.hpp>
#include "../include/boid.hpp"
#include "../include/algorithms/boids.hpp"

#include <memory>
#include <iostream>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    // Construct the boid sprites and pass the boid object as a unique_ptr to the vector to store the collection. 
    std::vector<std::unique_ptr<Boid>> boids;
    for (int i = 0; i < 50; i++){
        boids.push_back(std::make_unique<Boid>()); // append the boid to the boids vector as a unique_ptr to ensure memory is shared efficiently.
    }
    // Create the Boids Algorithm object to control the movement behavior for the boids in an easy interface. 
    BoidsAlgorithm boids_algorithm = BoidsAlgorithm(boids,1.0f,1.0f,1.0f); 
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        for (auto& boidPtr: boids){
            // Update the boids states using the existing boids algorithm params.
            boids_algorithm.update();
        }

        window.clear();
        window.display();
    }
}
