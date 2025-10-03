#ifndef KinematicWander_HPP
#define KinematicWander_HPP

#include "../steering_behavior.hpp"

class KinematicWander: public virtual KinematicMovement {
    public:
        KinematicWander() = default;
        ~KinematicWander() = default;
        KinematicSteeringOutput getSteering(Static& character) override;
};

#endif // KinematicWander_HPP