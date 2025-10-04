#include "../../include/steering/kinematic_arrive.hpp"

KinematicSteeringOutput KinematicArrive::getSteering(Static &character)
{
    // checking target to make sure the
    if (target.null_output == true)
    {
        auto result = KinematicSteeringOutput();
        result.null_output = true;
        return result;
    }
    else
    {
        KinematicSteeringOutput result = KinematicSteeringOutput();

        result.setVelocity(target.getPosition() - character.getPosition());

        // Check if we are approximately there, if so, return no steering
        if (result.getVelocity().length() <= m_stopRadius)
        {
            auto result = KinematicSteeringOutput();
            result.null_output = true;
            return result;
        }

        // We need to move to our target, we'd like to get there in in timeToTarget seconds
        result.setVelocity(result.getVelocity() / timeToTarget);

        // Check if the velocity is too fast, if so clip speed
        if (result.getVelocity().length() > m_maxSpeed)
        {
            result.setVelocity(result.getVelocity().normalized() * m_maxSpeed);
        }

        // Face in the direction we want to move
        sf::Angle newOrientation = sf::radians(getNewOrientation(character.getOrientation().asRadians(), result.getVelocity(), m_smoothing));
        character.setOrientation(newOrientation);

        // No angular acceleration

        return result;
    }
};