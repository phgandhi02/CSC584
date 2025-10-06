#ifndef Wander_HPP
#define Wander_HPP


#include "./kinematic_face.hpp"

class Wander: public KinematicFace {
    public:
        Wander() = default;
        ~Wander() = default;
        KinematicSteeringOutput getSteering(Static& character) override;
        float sampleDifference();
        // The forward offset of the wander circle.
        float wanderOffset = 1.0f;
        // The radius of the wander circle.
        float wanderRadius = 1.0f;

        // The maximum rate at which the wander orientation can change.
        float wanderRate = 1.0f;
    private:
        // The current orientation of the wander target.
        float m_wanderOrientation = 0.0f;
};

#endif // Wander_HPP