#ifndef KinematicFace_HPP
#define KinematicFace_HPP

#include "../steering/kinematic_align.hpp"

class KinematicFace: public KinematicAlign {
    public:
        KinematicFace() = default;
        ~KinematicFace() = default;
        KinematicSteeringOutput getSteering(Static& character) override;
    private:
};

#endif // KinematicFace_HPP