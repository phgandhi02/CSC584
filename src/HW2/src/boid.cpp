#include "../include/boid.hpp"

Boid::Boid(sf::Texture& texture, float speed, sf::Vector2f startPos)
    : m_texture(texture), m_sprite(texture)
{
    m_sprite.setPosition(startPos);
    m_sprite.setRotation(sf::radians(0.0f));
    breadcrumbs_on = true;
    m_breadcrumbs = Breadcrumbs();
    m_inputHandler = InputHandler();

    float m_speed = speed; 
    m_character = Static();
    m_character.setPositionVector(startPos);
    m_character.setOrientationFloat(0.0f);
    float m_rotation;
}

void Boid::update()
{
};

sf::Vector2f Boid::getPosition(){
    return m_character.getPositionVector();
};

KinematicSteeringOutput Boid::align(std::unique_ptr<KinematicMovement> align_steering){
    KinematicSteeringOutput steeringOutput = align_steering->getSteering(m_character);
    std::cout << "Steering Angle: " << steeringOutput.getRotationFloat() << 
        "Steering Velocity: " << steeringOutput.getVelocity().x << "," << steeringOutput.getVelocity().y 
        << std::endl;
    return steeringOutput;
}