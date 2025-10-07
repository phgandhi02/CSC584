#include "../../include/delegated_steering/wander.hpp"
#include "../../include/steering/kinematic_seek.hpp"

#include <iostream>
#include <random>

float Wander::sampleDifference()
{
    static std::default_random_engine rand_gen;
    std::uniform_real_distribution<> dis(0.0f, 1.0f);
    float randomValue = dis(rand_gen) - dis(rand_gen);
    return randomValue;
};

KinematicSteeringOutput Wander::checkCollision(Static &predictedCharacter, Static& character, sf::Vector2f velocity){
    const bool left_collision = 0 > predictedCharacter.getPosition().x;
    const bool right_collision = predictedCharacter.getPosition().x > m_windowSizeX;
    const bool up_collision = 0 > predictedCharacter.getPosition().y;
    const bool down_collision = predictedCharacter.getPosition().y > m_windowSizeY;

    // auto boid_pos = character.getPosition();

    if ((left_collision | right_collision | up_collision | down_collision))
    {
        auto seek_behavior = KinematicSeek();
        // seek_behavior.target = Static(newTarget, character.getOrientation());
        if (left_collision)
        {
            // auto offset = sf::Vector2f(wanderOffset,0.0f);
            auto offset = sf::Vector2f(m_windowSizeX,character.getPosition().y);  
            seek_behavior.target = Static(offset, sf::degrees(0.0f));
        }
        else if (right_collision)
        {
            // auto offset = sf::Vector2f(-wanderOffset,0.0f); 
            auto offset = sf::Vector2f(0.0f,character.getPosition().y); 
            seek_behavior.target = Static(offset, sf::degrees(180.0f));
        }
        else if (up_collision)
        {
            // auto offset = sf::Vector2f(0.0f,wanderOffset); 
            auto offset = sf::Vector2f(character.getPosition().x,m_windowSizeY); 
            seek_behavior.target = Static(offset, sf::degrees(90.0f));
        }
        else if (down_collision)
        {
           auto offset = sf::Vector2f(0.0f,character.getPosition().y); 
            seek_behavior.target = Static(offset, character.getOrientation());
        }
        std::cout << "Char.pos: " << character.getPosition().x  << " | " << character.getPosition().y << std::endl;
        std::cout << "Target.pos: " << seek_behavior.target.getPosition().x  << " | " << seek_behavior.target.getPosition().y << std::endl; 
        return seek_behavior.getSteering(predictedCharacter);
    } else {
        auto steering = KinematicSteeringOutput();
        steering.null_output = true;
        return steering;
    }
}

KinematicSteeringOutput Wander::getSteering(Static &character)
{
    auto direction = target.getPosition() - character.getPosition();
    auto distance = direction.length();

    m_wanderOrientation += sampleDifference() * wanderRate;

    auto targetOrientation = m_wanderOrientation - character.getOrientationFloat();

    auto characterUnitVector = sf::Vector2f(1.0f, character.getOrientation());
    auto targetPos = character.getPosition() + wanderOffset * characterUnitVector;

    auto targetUnitVector = sf::Vector2f(1.0f, targetOrientation);
    targetPos += wanderRadius * targetUnitVector;

    auto result = KinematicFace();

    result.target = Static(targetPos, sf::radians(targetOrientation));

    KinematicSteeringOutput faceSteeringOutput = result.getSteering(character);
    auto velocity = characterUnitVector * maxSpeed;
    faceSteeringOutput.setVelocity(velocity);

    auto speed = velocity.length();

    float prediction;
    if (speed <= (distance / maxPrediction)){ // check if speed gives us a reasonable prediction time
        prediction = maxPrediction;
    } else { // calculate the prediction time
        prediction = distance / speed;
    }

    auto predictedPosition = character.getPosition() + velocity*prediction;
    auto predictedCharacter = Static(predictedPosition,character.getOrientation());
    auto collisionSteering = checkCollision(predictedCharacter, character, velocity);

    if (collisionSteering.null_output == true){
        return faceSteeringOutput;
    } else {
        return collisionSteering;
    }
};