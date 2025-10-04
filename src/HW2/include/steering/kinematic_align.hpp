#ifndef KinematicAlign_HPP
#define KinematicAlign_HPP

#include "../steering_behavior.hpp"

class KinematicAlign: public virtual KinematicMovement {
    public:
        KinematicAlign() = default;
        ~KinematicAlign() = default;
        KinematicSteeringOutput getSteering(Static& character) override;
        void updateTarget(const Static targetPos);
    private:
        Static m_target;
        float m_smoothing = 0.0f;
        sf::Angle m_maxAngularAcceleration = sf::degrees(30.0f); // Maximum angular acceleration
        sf::Angle m_maxRotation = sf::degrees(20.0f); // Maximum rotation speed

        sf::Angle m_rotationSize = sf::Angle(sf::degrees(0.1f)); // Threshold to consider aligned
        sf::Angle m_targetRadius = sf::degrees(5.0f); // Radius for arriving at target orientation
        sf::Angle m_slowRadius = sf::degrees(30.0f); // Radius for beginning to slow down

        sf::Angle m_timeToTarget = sf::degrees(0.1f); // Time over which to achieve target speed
};

#endif // KinematicAlign_HPP