#include "../include/boid.hpp"
const float PI_F = 3.14159265358979f;

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
};

// Main function to run in the game loop. Updates boid m_character based on steering behavior pointed to m_controller.
void Boid::update(float dt)
{
    // Assign target from mouse click using input handler object.
    auto target = m_inputHandler->update(); // update will return a Static object with null_output false;
    
    // Check if boid has a valid steering behavior attached.
    if (m_controller == nullptr){
        return; // if it doesn't have a valid steering behavior then return and don't update m_character.
    }

    // set the target for the controller equal to the target from the input handler (ie. mouse)
    m_controller->target = target;

    // Get the steering behavior to return how the boid should move based on the target.
    m_steering = m_controller->getSteering(m_character);

    // Check if the steering output is valid.
    if (m_steering.null_output == false)
    {
        // Update the position and orientation
        m_character.setPosition(m_character.getPosition() + m_steering.getVelocity() * dt);
        m_character.setOrientation(m_character.getOrientation() + m_steering.getRotation() * dt);

        // Wrap orientation between [-pi, pi)
        if (sf::radians(PI_F) <= m_character.getOrientation())
            m_character.setOrientation(m_character.getOrientation() - sf::radians(2 * PI_F));
        else if (sf::radians(-PI_F) > m_character.getOrientation())
            m_character.setOrientation(m_character.getOrientation() + sf::radians(2 * PI_F));        

        // Update the sprite position and rotation
        m_sprite.setPosition(m_character.getPosition());
        m_sprite.setRotation(m_character.getOrientation() + sf::degrees(90.0f)); //AI-gen: Adjust for sprite facing up
    }
};

// Helper function to get the Boid's current position
sf::Vector2f Boid::getPosition(){
    return m_character.getPosition();
};

// Helper function to set the Boid texture
void Boid::setTexture(sf::Texture &texture){
    m_sprite.setTexture(texture);
}