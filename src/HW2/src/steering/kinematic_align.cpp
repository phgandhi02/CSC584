#include "../../include/steering/kinematic_align.hpp"
#include <iostream>

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

  std::cout << "Align: chararcter.orient = " << character.getOrientationFloat() << std::endl;
  // Linear velocity is zero

  auto result = KinematicSteeringOutput();
  result.null_output = true;
  return result;
};