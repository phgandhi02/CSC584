#ifndef KinematicWander_HPP
#define KinematicWander_HPP

#include "../steering_behavior.hpp"

class KinematicWander: public virtual KinematicMovement {
    public:
        KinematicWander() = default;
        ~KinematicWander() = default;
        float sampleDifference();
        KinematicSteeringOutput getSteering(Static& character) override;
    private:
        float m_rotation;
        int m_framesSinceSample;

        int m_samplingInterval;
        float m_maxRotation;
        float m_maxSpeed;
};

#endif // KinematicWander_HPP