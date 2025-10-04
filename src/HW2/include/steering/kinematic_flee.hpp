#ifndef KinematicFlee_HPP
#define KinematicFlee_HPP

#include "../steering_behavior.hpp"

class KinematicFlee: public virtual KinematicMovement {
    public:
        KinematicFlee() = default;
        ~KinematicFlee() = default;
        KinematicSteeringOutput getSteering(Static& character) override;
    private:
        float m_maxSpeed = 250.0f;
        float m_smoothing = 0.01f;
};

#endif // KinematicFlee_HPP