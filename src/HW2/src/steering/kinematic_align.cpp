#include "../../include/steering/kinematic_align.hpp"

void KinematicAlign::updateTarget(const Static target){
    m_target = target;
}

KinematicSteeringOutput KinematicAlign::getSteering(Static& character){
    // checking m_target to make sure the
  if (m_target.null_output == true)
  {
    auto result = KinematicSteeringOutput();
    result.null_output = true;
    return result;
  }
  else
  {
    updateTarget(m_target);
    KinematicSteeringOutput result = KinematicSteeringOutput();
    sf::Angle direction = m_target.getOrientation() - character.getOrientation();

    direction = direction.wrapSigned();
    m_rotationSize = sf::radians(std::abs(direction.asRadians()));

    // Check if we are there, return no steering.
    if (m_rotationSize < m_targetRadius)
    {
      auto result = KinematicSteeringOutput();
    result.null_output = true;
    return result;
    }

    // If we are outside the slow radius, then use maximum rotation
    if (m_rotationSize > m_slowRadius)
    {
      result.setRotation(m_maxRotation);
    }
    else
    { // Otherwise calculate a scaled rotation
      float rotationSpeed = m_maxRotation.asRadians() * m_rotationSize.asRadians();
      sf::Angle targetRotation = sf::radians(rotationSpeed / m_slowRadius.asRadians());
      result.setRotation(targetRotation);
    }

    // The final target rotation combines speed (already in the varaible) and direction
    result.setRotation(result.getRotation() * direction.asRadians() / m_rotationSize.asRadians());

    // Acceleration tries to get to the target rotation
    result.setRotation(sf::radians((result.getRotationFloat() - character.getOrientationFloat()) / m_timeToTarget.asRadians()));

    // Check if the acceleration is too great
    float angularAcceleration = std::abs(result.getRotationFloat());
    if (angularAcceleration > m_maxAngularAcceleration.asRadians())
    {
      result.setRotation(sf::radians((result.getRotationFloat() / angularAcceleration) * m_maxAngularAcceleration.asRadians()));
    }

    // Linear velocity is zero

    return result;
  }
};