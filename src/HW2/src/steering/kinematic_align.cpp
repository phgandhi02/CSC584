#include "../../include/steering/kinematic_align.hpp"

KinematicSteeringOutput KinematicAlign::getSteering(Static &character)
{
  // checking m_target to make sure the
  if (target.null_output == true)
  {
    auto result = KinematicSteeringOutput();
    result.null_output = true;
    return result;
  }
  auto direction = target.getPosition() - character.getPosition();
  character.setOrientationFloat(getNewOrientation(character.getOrientationFloat(), direction, smoothing));
  // Linear velocity is zero

  auto result = KinematicSteeringOutput();
  result.null_output = true;
  return result;
};