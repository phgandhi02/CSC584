#include "../../include/steering/kinematic_wander.hpp"

#include <random>

float KinematicWander::sampleDifference()
{
    static std::default_random_engine rand_gen;
    std::uniform_real_distribution<> dis(0.0f, 1.0f);
    float randomValue = dis(rand_gen) - dis(rand_gen);
    return randomValue;
};

KinematicSteeringOutput KinematicWander::getSteering(Static& character){
   if (0 == m_framesSinceSample){
        m_rotation = sampleDifference() * m_maxRotation;
    }
    m_framesSinceSample = (m_framesSinceSample + 1) % m_samplingInterval;

    KinematicSteeringOutput result = KinematicSteeringOutput();
    
    // Get velocity from the vector form of the orientation
    auto newVelocity = sf::Vector2f(cos(character.getOrientation().asRadians()) * maxSpeed, -1.0f * sin(character.getOrientation().asRadians()) * maxSpeed);
    result.setVelocity(newVelocity); // set velocity in the direction of the character's orientation

    // Change our orientation randomly
    result.setRotation(sf::radians(m_rotation));
    
    return result;
};