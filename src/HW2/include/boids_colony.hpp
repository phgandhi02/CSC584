#ifndef BOIDS_HPP
#define BOIDS_HPP

#include "./boid.hpp"
#include <iostream>

class BoidsColony{
    public:
        BoidsColony(
            const sf::Texture &texture, 
            sf::RenderWindow& window, 
            float separation, 
            float alignment, 
            float cohesion,
            int boidCount
        );
        // BoidsColony(const sf::Texture &texture, Static startPos, sf::RenderWindow& window);
        ~BoidsColony() = default;
        void setSteering(Boid &self);
        void update();
        void draw(sf::RenderWindow &window);
        std::vector<Boid> boids;
        float separation = 1.0f/3.0f;
        float alignment = 1.0f/3.0f;
        float cohesion = 1.0f/3.0f;
        float neighborRadiusThreshold = 10.0f;
};

#endif // BOIDS_HPP