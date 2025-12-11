#include "../../../include/movement/delegated_steering/kinematic_face.hpp"
#include <iostream>

KinematicSteeringOutput KinematicFace::getSteering(Static &character)
{
    auto direction = target.getPosition() - character.getPosition();

    if (direction.length() == 0.0f)
    {
        return KinematicSteeringOutput();
    }

    auto align = KinematicAlign();
    align.target = target;
    align.target.setOrientationFloat(atan2(-direction.x, direction.y));
    return align.getSteering(character);
};