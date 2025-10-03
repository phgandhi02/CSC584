#ifndef STEERING_BEHAVIOR_HPP
#define STEERING_BEHAVIOR_HPP

#include <SFML/Graphics.hpp>
#include <optional>
#include <cmath>
#include "./utils.hpp"

/**
 * @class Static
 * @brief Represents the static properties of a game object, such as position and orientation.
 * 
 * Provides methods to get and set the position and orientation of the object.
 * 
 * @note Documentation AI generated.
 */
class Static {
    public:
    // Constructors and deconstructors
        Static(): m_position(sf::Vector2f(0.0f,0.0f)), m_orientation(sf::Angle(sf::degrees(0.0f))) {};
        Static(sf::Vector2f position,sf::Angle orientation): m_position(position), m_orientation(orientation) {};
        ~Static() = default;
    // Getters and Setters for member variables
        sf::Vector2f getPositionVector() { return m_position; }
        sf::Angle getOrientationAngle() { return m_orientation; }
        float getOrientationFloat() { return m_orientation.asRadians(); }
        void setPositionVector(sf::Vector2f position) { m_position = position; }
        void setPositionFloat(float x, float y) { m_position = sf::Vector2f(x,y); }
        void setOrientationAngle(sf::Angle orientation) { m_orientation = orientation; }
        void setOrientationFloat(float orientation) { m_orientation = sf::radians(orientation); } // Set Orientation in radians
    private:
        sf::Vector2f m_position;
        sf::Angle m_orientation;
};

/**
 * @class KinematicSteeringOutput
 * @brief Encapsulates the output of a kinematic steering behavior, including velocity and rotation.
 * 
 * This class stores the velocity and rotation resulting from a steering calculation.
 * It provides constructors for default initialization and for setting custom values.
 * 
 * @note Documentation AI generated.
 */
class KinematicSteeringOutput {
    public:
        /**
         * @brief Default constructor.
         * 
         * Initializes velocity to (0, 0) and rotation to zero angle.
         */
        KinematicSteeringOutput(): m_velocity(sf::Vector2f(0.0f,0.0f)), m_rotation(sf::Angle()) {};

        /**
         * @brief Parameterized constructor.
         * 
         * Initializes velocity and rotation to the provided values.
         * 
         * @param velocity The initial velocity vector.
         * @param rotation The initial rotation angle.
         */
        KinematicSteeringOutput(sf::Vector2f velocity, sf::Angle rotation);

        /**
         * @brief Default destructor.
         */
        ~KinematicSteeringOutput() = default;

        // Getters and Setters
        sf::Vector2f getVelocity() { return m_velocity; }
        sf::Angle getRotationAngle() { return m_rotation; }
        float getRotationFloat() { return m_rotation.asRadians(); }
        void setVelocity(sf::Vector2f velocity) { m_velocity = velocity; }
        void setRotation(sf::Angle rotation) { m_rotation = rotation; }
        void setRotationFloat(float rotation) { m_rotation = sf::radians(rotation); } // Set Orientation in radians
    private:
        sf::Vector2f m_velocity;
        sf::Angle m_rotation; // rotation uses Angle type to make unit conversion easy.
};

/**
 * @class KinematicMovement
 * @brief Abstract base class defining the contract for kinematic movement behaviors.
 * 
 * Provides an interface for obtaining steering output for a game object.
 * Derived classes should implement the getSteering method.
 * 
 * @note Documentation AI generated.
 */
class KinematicMovement {
    public:
        // Constructors and Deconstructors
        KinematicMovement() = default;
        virtual ~KinematicMovement() = default; // Good practice to have a virtual destructor - AI Generated

        // Getters and Setters
        // getSteering will return either a unique ptr to a KinematicSteeringOutput or a nullptr
        /*
        Pure abstract functions must be declared with 0 in order to create a strong contract for derived classes.
        The strong contract forces all derived classes to implement the pure virtual function, ensuring consistent 
        behavior across different implementations.
        */
        float getNewOrientation(float orientation, sf::Vector2f velocity, float smoothing);
        virtual KinematicSteeringOutput getSteering(Static& character) = 0; // pure virtual function to pass a reference to character for efficiency
    private:
};

#endif // STEERING_BEHAVIOR_HPP