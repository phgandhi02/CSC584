#include "../../include/steering/kinematic_seek.hpp"

KinematicSteeringOutput KinematicSeek::getSteering(Static &character)
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
        result.setVelocity(target.getPosition() - character.getPosition());
        result.setVelocity(result.getVelocity().normalized() * m_maxSpeed);

        sf::Angle newOrientation = sf::radians(getNewOrientation(character.getOrientation().asRadians(), result.getVelocity(), m_smoothing));
        character.setOrientation(newOrientation);

        return result;
    }
}