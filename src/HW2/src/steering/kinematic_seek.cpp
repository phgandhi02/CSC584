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
        if (result.getVelocity().x == 0.0f && result.getVelocity().y == 0.0f)
        {
            auto result = KinematicSteeringOutput();
            result.null_output = true;
            return result;
        }
        result.setVelocity(result.getVelocity().normalized() * maxSpeed);

        sf::Angle newOrientation = sf::radians(getNewOrientation(character.getOrientation().asRadians(), result.getVelocity(), smoothing));
        character.setOrientation(newOrientation);

        return result;
    }
}