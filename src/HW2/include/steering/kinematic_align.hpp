#ifndef KinematicAlign_HPP
#define KinematicAlign_HPP

#include "../steering_behavior.hpp"

class KinematicAlign: public virtual KinematicMovement {
    public:
        KinematicAlign() = default;
        ~KinematicAlign() = default;
        KinematicSteeringOutput getSteering(Static& character) override;
};

#endif // KinematicAlign_HPP