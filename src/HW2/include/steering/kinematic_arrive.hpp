#ifndef KinematicArrive_HPP
#define KinematicArrive_HPP

#include "../steering_behavior.hpp"

class KinematicArrive: public virtual KinematicMovement {
    public:
        KinematicArrive(float timeToTarget): m_timeToTarget(timeToTarget) {};
        ~KinematicArrive() = default;
        void updateTarget(Static targetPos);
        KinematicSteeringOutput getSteering(Static& character) override;
    private:
        float m_timeToTarget;
        float m_stopRadius = .01f;
};

#endif // KinematicArrive_HPP