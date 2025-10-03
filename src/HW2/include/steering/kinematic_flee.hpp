#ifndef KinematicFlee_HPP
#define KinematicFlee_HPP

#include "../steering_behavior.hpp"

class KinematicFlee: public virtual KinematicMovement {
    public:
        KinematicFlee() = default;
        ~KinematicFlee() = default;
        KinematicSteeringOutput getSteering(Static& character) override;
};

#endif // KinematicFlee_HPP