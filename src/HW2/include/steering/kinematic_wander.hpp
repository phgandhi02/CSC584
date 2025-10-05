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
        float m_rotation = 0.0f;
        int m_framesSinceSample = 0;

        int m_samplingInterval = 4;
        float m_maxRotation = 3.14159265358979323846f;
};

#endif // KinematicWander_HPP