#ifndef KinematicSeek_HPP
#define KinematicSeek_HPP

#include "../steering_behavior.hpp"

class KinematicSeek: public virtual KinematicMovement {
    public:
        KinematicSeek() = default;
        ~KinematicSeek() = default;
        KinematicSteeringOutput getSteering(Static& character) override;
    private:
        float m_maxSpeed = 250.0f;
        float m_smoothing = 0.0f;
};

#endif // KinematicSeek_HPP