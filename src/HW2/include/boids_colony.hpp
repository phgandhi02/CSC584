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
        float separation;
        float alignment;
        float cohesion;
        float neighborRadiusThreshold;
};

#endif // BOIDS_HPP