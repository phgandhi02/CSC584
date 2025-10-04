#ifndef KinematicArrive_HPP
#define KinematicArrive_HPP

#include "../steering_behavior.hpp"

class KinematicArrive: public virtual KinematicMovement {
    public:
        KinematicArrive() = default;
        ~KinematicArrive() = default;
        void updateTarget(Static targetPos);
        KinematicSteeringOutput getSteering(Static& character) override;
        float timeToTarget;
    private:
        float m_maxSpeed = 250.0f;
        float m_smoothing = 1.0f; // const between 0-1
        float m_stopRadius = .01f;
};

#endif // KinematicArrive_HPP