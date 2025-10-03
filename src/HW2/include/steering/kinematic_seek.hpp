#ifndef KinematicSeek_HPP
#define KinematicSeek_HPP

#include "../steering_behavior.hpp"

class KinematicSeek: public virtual KinematicMovement {
    public:
        KinematicSeek() = default;
        ~KinematicSeek() = default;
        KinematicSteeringOutput getSteering(Static& character) override;
};

#endif // KinematicSeek_HPP