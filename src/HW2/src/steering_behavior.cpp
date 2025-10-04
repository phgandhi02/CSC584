#include "../include/steering_behavior.hpp"

KinematicSteeringOutput::KinematicSteeringOutput(sf::Vector2f velocity, sf::Angle rotation)
{
    this->m_velocity = velocity;
    this->m_rotation = rotation;
};

bool KinematicSteeringOutput::operator==(KinematicSteeringOutput& other){
    if (other.getRotation() != this->getRotation()){
        return false;
    } else if(other.getVelocity() != this->getVelocity()){
        return false;
    } else {
        return true;
    }
};

/*
Returns the new orientation (rads) based on the current orientation (rads) and velocity.
*/
float KinematicMovement::getNewOrientation(float orientation, sf::Vector2f velocity, float smoothing)
{
    const float PI_F = 3.14159265358979f;
    if (velocity.length() >= .001f){
        float target = std::atan2(-velocity.y, velocity.x);
        if (.0f < smoothing)
        {
            float delta = (target - orientation);

            if (PI_F < delta)
                delta -= 2*PI_F;
            else if (-PI_F > delta)
                delta += 2*PI_F;

            return orientation + delta * smoothing;
        }

        return target;
    }

    return orientation; // radians
};