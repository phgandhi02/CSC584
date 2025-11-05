#include "../../../include/movement/steering/kinematic_flee.hpp"

KinematicSteeringOutput KinematicFlee::getSteering(Static &character)
{
    if (target.null_output == true)
    {
        auto result = KinematicSteeringOutput();
        result.null_output = true;
        return result;
    }
    else
    {
        KinematicSteeringOutput result = KinematicSteeringOutput();
        sf::Vector2f vectorDistance = character.getPosition() - target.getPosition();
        if (vectorDistance == sf::Vector2f())
        {

            vectorDistance = sf::Vector2f(maxSpeed, target.getOrientation());
            // vectorDistance = sf::Vector2f(m_maxSpeed*sqrt(2.0f),m_maxSpeed*sqrt(2.0f));
        }
        result.setVelocity(vectorDistance);
        if (result.getVelocity().length() != 0.0f)
        {
            result.setVelocity(result.getVelocity().normalized() * maxSpeed);
        }

        sf::Angle newOrientation = sf::radians(getNewOrientation(character.getOrientation().asRadians(), result.getVelocity(), smoothing));
        character.setOrientation(newOrientation);

        return result;
    }
};