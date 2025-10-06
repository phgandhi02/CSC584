#include "../../include/steering/kinematic_wander.hpp"

#include <random>

float KinematicWander::sampleDifference()
{
    static std::default_random_engine rand_gen;
    std::uniform_real_distribution<> dis(0.0f, 1.0f);
    float randomValue = dis(rand_gen) - dis(rand_gen);
    return randomValue;
};

KinematicSteeringOutput KinematicWander::getSteering(Static &character)
{
    auto orientation = character.getOrientation();

    if (0 == m_framesSinceSample)
    {
        wanderRotation = sampleDifference() * m_maxRotation;
    }
    m_framesSinceSample = (m_framesSinceSample + 1) % samplingInterval;

    KinematicSteeringOutput result = KinematicSteeringOutput();

    // Get velocity from the vector form of the orientation
    auto newVelocity = sf::Vector2f();
    newVelocity.x = cos(orientation.asRadians()) * maxSpeed;
    newVelocity.y = sin(orientation.asRadians()) * maxSpeed;

    // std::cout << newVelocity.x << " | " << newVelocity.y << std::endl;

    result.setVelocity(newVelocity); // set velocity in the direction of the character's orientation

    // Change our orientation randomly
    result.setRotation(sf::radians(wanderRotation));

    // character.setOrientationFloat(getNewOrientation(orientation.asRadians(), newVelocity, smoothing));

    return result;
};