#ifndef KinematicArrive_HPP
#define KinematicArrive_HPP

#include "../steering_behavior.hpp"

class KinematicArrive: public virtual KinematicMovement {
    public:
        KinematicArrive() = default;
        ~KinematicArrive() = default;
        KinematicSteeringOutput getSteering(Static& character) override;
};

#endif // KinematicArrive_HPP