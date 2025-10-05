#ifndef KinematicSeek_HPP
#define KinematicSeek_HPP

#include "../steering_behavior.hpp"

class KinematicSeek: public virtual KinematicMovement {
    public:
        KinematicSeek() = default;
        ~KinematicSeek() = default;
        KinematicSteeringOutput getSteering(Static& character) override;
    private:

};

#endif // KinematicSeek_HPP