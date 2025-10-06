#include "../../include/delegated_steering/wander.hpp"

#include <iostream>
#include <random>

float Wander::sampleDifference()
{
    static std::default_random_engine rand_gen;
    std::uniform_real_distribution<> dis(0.0f, 1.0f);
    float randomValue = dis(rand_gen) - dis(rand_gen);
    return randomValue;
};

KinematicSteeringOutput Wander::getSteering(Static &character) {
    m_wanderOrientation += sampleDifference() * wanderRate;

    auto targetOrientation = m_wanderOrientation - character.getOrientationFloat();

    auto characterUnitVector = sf::Vector2f(1.0f,character.getOrientation());
    auto targetPos = character.getPosition() + wanderOffset*characterUnitVector;
    
    auto targetUnitVector = sf::Vector2f(1.0f,targetOrientation);
    targetPos += wanderRadius * targetUnitVector;

    auto result = KinematicFace();
    
    result.target = Static(targetPos,sf::radians(targetOrientation));

    KinematicSteeringOutput faceSteeringOutput = result.getSteering(character);
    faceSteeringOutput.setVelocity(characterUnitVector*maxSpeed);

    return faceSteeringOutput;
};