#ifndef KinematicWander_HPP
#define KinematicWander_HPP

#include "../steering_behavior.hpp"

class KinematicWander: public virtual KinematicMovement {
    public:
        KinematicWander() = default;
        KinematicWander(float wanderRotation, int samplingInterval)
            : wanderRotation(wanderRotation), samplingInterval(samplingInterval) {};
        ~KinematicWander() = default;
        float sampleDifference();
        KinematicSteeringOutput getSteering(Static& character) override;
        float wanderRotation = 0.0f;
        int samplingInterval = 4;
    private:
        int m_framesSinceSample = 0;
        float m_maxRotation = 3.14159265358979323846f;
};

#endif // KinematicWander_HPP