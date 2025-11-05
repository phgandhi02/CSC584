#ifndef STEERING_BEHAVIOR_HPP
#define STEERING_BEHAVIOR_HPP

#include <SFML/Graphics.hpp>

#include <optional>
#include <cmath>
#include <iostream>

/**
 * @class Static
 * @brief Represents the static properties of a game object, such as position and orientation.
 *
 * Provides methods to get and set the position and orientation of the object.
 *
 * @note Documentation AI generated.
 */
class Static
{
public:
    // Constructors and deconstructors
    Static() : m_position(sf::Vector2f(0.0f, 0.0f)), m_orientation(sf::Angle(sf::radians(0.0f))) {};
    Static(sf::Vector2f position, sf::Angle orientation) : m_position(position), m_orientation(orientation) {};
    ~Static() = default;
    bool null_output = false;
    bool operator==(Static &other);

    // Getters and Setters for member variables
    sf::Vector2f getPosition() { return m_position; }
    sf::Angle getOrientation() { return m_orientation; }
    // get character orientation in radians
    float getOrientationFloat() { return m_orientation.asRadians(); }
    void setPosition(sf::Vector2f position) { m_position = position; }
    void setPositionFloat(float x, float y) { m_position = sf::Vector2f(x, y); }
    void setOrientation(sf::Angle orientation) { m_orientation = orientation; }
    // Set Orientation in radians
    void setOrientationFloat(float orientation) { m_orientation = sf::radians(orientation); }

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
class KinematicSteeringOutput
{
public:
    /**
     * @brief Default constructor.
     *
     * Initializes velocity to (0, 0) and rotation to zero angle.
     */
    KinematicSteeringOutput() : null_output(false), m_velocity(sf::Vector2f(0.0f, 0.0f)), m_rotation(sf::Angle()) {};

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

    // KinematicSteeringOutput& operator= (const KinematicSteeringOutput& other);
    bool operator==(KinematicSteeringOutput &other);
    bool null_output = false;

    // Getters and Setters
    sf::Vector2f getVelocity() { return m_velocity; }
    sf::Angle getRotation() { return m_rotation; }
    float getRotationFloat() { return m_rotation.asRadians(); }
    void setVelocity(sf::Vector2f velocity) { m_velocity = velocity; }
    void setRotation(sf::Angle rotation) { m_rotation = rotation; }
    // Set Orientation in degrees
    void setRotationFloat(float rotation) { m_rotation = sf::radians(rotation); }

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
class KinematicMovement
{
public:
    // Constructors and Deconstructors
    KinematicMovement() = default;
    virtual ~KinematicMovement() = default; // Good practice to have a virtual destructor - AI Generated

    // Getters and Setters
    float getNewOrientation(float orientation, sf::Vector2f velocity, float smoothing);
    virtual KinematicSteeringOutput getSteering(Static &character) = 0; // pure virtual function to pass a reference to character for efficiency
    Static target;
    float smoothing = 0.1f; // const between 0-1 to tune how snappy orientation change is.
    float maxSpeed = 100.0f;
};

#endif // STEERING_BEHAVIOR_HPP