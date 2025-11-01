#ifndef BOIDS_HPP
#define BOIDS_HPP

#include "./boid.hpp"
#include <iostream>

class BoidsColony
{
public:
    BoidsColony(
        const sf::Texture &texture,
        sf::RenderWindow &window,
        float separation,
        float cohesion,
        float alignment,
        int boidCount);
    // BoidsColony(const sf::Texture &texture, Static startPos, sf::RenderWindow& window);
    ~BoidsColony() = default;
    void setSteering(Boid &self);
    void update();
    void draw(sf::RenderWindow &window);
    std::vector<Boid> boids;
    float separation = 1.0f / 3.0f;
    float alignment = 1.0f / 3.0f;
    float cohesion = 1.0f / 3.0f;

    float separationRadius = 20.0f;
    float cohesionRadius = 75.0f;
    float alignmentRadius = 100.0f;

    bool mouseInputOn = true;

private:
    unsigned int m_windowSizeX = 800;
    unsigned int m_windowSizeY = 600;
    InputHandler m_inputHandler;
    unsigned int m_boidCount;
};

#endif // BOIDS_HPP