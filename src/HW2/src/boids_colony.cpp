#include "../include/boids_colony.hpp"
#include "../include/steering/kinematic_align.hpp"
#include "../include/steering/kinematic_seek.hpp"
#include "../include/steering/kinematic_flee.hpp"

#include <random>

float sampleDifference(float leftBound, float rightBound)
{
    static std::default_random_engine rand_gen;
    std::uniform_real_distribution<> dis(leftBound, rightBound);
    float randomValue = dis(rand_gen);
    return randomValue;
};

BoidsColony::BoidsColony(const sf::Texture &texture, sf::RenderWindow &window,
                         float separation, float alignment, float cohesion, int boidCount)
                         : separation(separation), alignment(alignment), cohesion(cohesion)
{
    for (int i = 0; i < boidCount; i++)
    {
        auto windowSizeX = (float)window.getSize().x;
        auto windowSizeY = (float)window.getSize().y;

        auto startPos = sf::Vector2f(sampleDifference(0, windowSizeX), sampleDifference(0, windowSizeY));
        auto startOrient = sf::degrees(sampleDifference(0, 360));

        Static startChar = Static(startPos, startOrient);
        boids.emplace_back(texture, startChar, window);
        // std::cout << startPos.x << " | " << startPos.y << std::endl;
    }
};

void BoidsColony::setSteering(Boid &self)
{
    auto align = KinematicAlign();
    auto seek = KinematicSeek();
    auto flee = KinematicFlee();

    auto separationForce = sf::Vector2f();
    for (Boid &boid : boids)
    {
        const auto direction = self.getCharacter().getPosition() - boid.getCharacter().getPosition();
        const auto distance = direction.length();
        if (neighborRadiusThreshold > distance && distance > 0.0f)
        {
            auto fleeVector = direction / distance;
            separationForce += fleeVector;
        }
    }
    seek.target = Static(sf::Vector2f(self.getCharacter().getPosition() + separationForce), self.getCharacter().getOrientation());
    self.m_controller = std::move(std::make_unique<KinematicSeek>(seek));
};

// Implement update() method
void BoidsColony::update()
{
    // Your update logic here
    for (Boid &boid : boids)
    {
        setSteering(boid);
        boid.update(0.01f);
        
    }
}

void BoidsColony::draw(sf::RenderWindow &window)
{
    // Your update logic here
    for (Boid &boid : boids)
    {
        boid.draw(window);
    }
}