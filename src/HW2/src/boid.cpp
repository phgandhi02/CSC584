#include "../include/boid.hpp"

Boid::Boid(const sf::Texture& texture, float speed, sf::Vector2f startPos)
    : m_sprite(texture)
{
    m_sprite.setPosition(startPos);
    m_sprite.setRotation(sf::radians(0.0f));
    breadcrumbs_on = true;
    m_breadcrumbs = Breadcrumbs();
    m_inputHandler = InputHandler();

    float m_speed = speed; 
    m_character = Static();
    m_character.setPosition(startPos);
    m_character.setOrientationFloat(0.0f);
    float m_rotation;
}

void Boid::update(float dt)
{
    const float PI_F = 3.14159265358979f;
    if (m_controller == nullptr){
        return;
    }

    m_steering =m_controller->getSteering(m_character);

    if (m_steering.null_output == false)
    {
        // Update the position and orientation
        m_character.setPosition(m_character.getPosition() + m_steering.getVelocity() * dt);
        m_character.setOrientation(m_character.getOrientation() + m_steering.getRotation() * dt);

        if (sf::radians(PI_F) < m_character.getOrientation())
            m_character.setOrientation(m_character.getOrientation() - sf::radians(2 * PI_F));
        else if (sf::radians(-PI_F) > m_character.getOrientation())
            m_character.setOrientation(m_character.getOrientation() + sf::radians(2 * PI_F));        

        // Update the sprite position and rotation
        m_sprite.setPosition(m_character.getPosition());
        m_sprite.setRotation(m_character.getOrientation() + sf::degrees(90.0f)); //AI-gen: Adjust for sprite facing up
    }
};

sf::Vector2f Boid::getPosition(){
    return m_character.getPosition();
};

// KinematicSteeringOutput Boid::align(std::unique_ptr<KinematicMovement> align_steering){
//     KinematicSteeringOutput steeringOutput = align_steering->getSteering(m_character);
//     std::cout << "Steering Angle: " << steeringOutput.getRotationFloat() << 
//         "| Steering Velocity: " << steeringOutput.getVelocity().x << "," << steeringOutput.getVelocity().y 
//         << std::endl;
//     return steeringOutput;
// };

void Boid::setTexture(sf::Texture &texture){
    m_sprite.setTexture(texture);
}