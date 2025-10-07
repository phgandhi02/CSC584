#ifndef Wander_HPP
#define Wander_HPP


#include "./kinematic_face.hpp"

class Wander: public KinematicFace {
    public:
        Wander(unsigned int windowSizeX, unsigned int windowSizeY)
            :m_windowSizeX(windowSizeX), m_windowSizeY(windowSizeY) {};
        ~Wander() = default;
        KinematicSteeringOutput getSteering(Static& character) override;
        KinematicSteeringOutput checkCollision(Static& predictedCharacter,Static& character, sf::Vector2f velocity);
        float sampleDifference();
        // The forward offset of the wander circle.
        float wanderOffset = 1.0f;
        // The radius of the wander circle.
        float wanderRadius = 1.0f;

        // The maximum rate at which the wander orientation can change.
        float wanderRate = 1.0f;

        float maxPrediction = 0.5f;

        float avoidDistance = 1.0f;
    private:
        // The current orientation of the wander target.
        float m_wanderOrientation = 0.0f;

        unsigned int m_windowSizeX;
        unsigned int m_windowSizeY;
};

#endif // Wander_HPP