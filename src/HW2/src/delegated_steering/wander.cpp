#include "../../include/delegated_steering/wander.hpp"
#include "../../include/steering/kinematic_seek.hpp"
#include "../../include/steering/kinematic_align.hpp"

#include <iostream>
#include <random>

float Wander::sampleDifference()
{
    static std::default_random_engine rand_gen;
    std::uniform_real_distribution<> dis(0.0f, 1.0f);
    float randomValue = dis(rand_gen) - dis(rand_gen);
    return randomValue;
};

KinematicSteeringOutput Wander::checkCollision(Static &predictedCharacter, Static &character, sf::Vector2f velocity)
{
    const bool left_collision = 0 > predictedCharacter.getPosition().x;
    const bool right_collision = predictedCharacter.getPosition().x > m_windowSizeX;
    const bool up_collision = 0 > predictedCharacter.getPosition().y;
    const bool down_collision = predictedCharacter.getPosition().y > m_windowSizeY;

    // used Gemini to get inspired to use center of window as newTarget
    float minWindowSize = (float)std::min(m_windowSizeX, m_windowSizeY);
    auto newTarget = sf::Vector2f(m_windowSizeX / 2.0f, m_windowSizeY / 2.0f) + minWindowSize * sf::Vector2f(sampleDifference(), sampleDifference());

    if ((left_collision | right_collision | up_collision | down_collision))
    {
        auto align_behavior = KinematicAlign();
        align_behavior.smoothing = 0.0f;

        align_behavior.target = Static(newTarget, character.getOrientation());
        align_behavior.getSteering(character);

        auto seek_behavior = KinematicSeek();
        seek_behavior.target = Static(newTarget, character.getOrientation());
        return seek_behavior.getSteering(character);
    }
    else
    {
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
    if (speed <= (distance / maxPrediction))
    { // check if speed gives us a reasonable prediction time
        prediction = maxPrediction;
    }
    else
    { // calculate the prediction time
        prediction = distance / speed;
    }

    auto predictedPosition = character.getPosition() + velocity * prediction;
    auto predictedCharacter = Static(predictedPosition, character.getOrientation());
    auto collisionSteering = checkCollision(predictedCharacter, character, velocity);

    if (collisionSteering.null_output == true)
    {
        return faceSteeringOutput;
    }
    else
    {
        return collisionSteering;
    }
};