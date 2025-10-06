#include "../include/boid.hpp"
#include <iostream>

const float PI_F = 3.14159265358979f;

Boid::Boid(const sf::Texture &texture, Static startPos, sf::RenderWindow& window)
    : m_sprite(texture), m_inputHandler(window)
{
    m_sprite.setPosition(startPos.getPosition());
    m_sprite.setRotation(startPos.getOrientation());
    breadcrumbs_on = true;
    m_breadcrumbs = Breadcrumbs();
    m_character = startPos;
    float m_rotation;
};

// Main function to run in the game loop. Updates boid m_character based on steering behavior pointed to m_controller.
void Boid::update(float dt)
{
    // Check if boid has a valid steering behavior attached.
    if (m_controller == nullptr)
    {
        std::cout << "no steering behavior" << std::endl;
        return; // if it doesn't have a valid steering behavior then return and don't update m_character.
    }

    if (!unittesting)
    {
        // Assign target from mouse click using input handler object.
        auto target = m_inputHandler.update(); // update will return a Static object with null_output false;
        // set the target for the controller equal to the target from the input handler (ie. mouse)
        m_controller->target = target;
    }

    m_controller->smoothing = smoothing;
    m_controller->maxSpeed = speed;

    // Get the steering behavior to return how the boid should move based on the target.
    m_steering = m_controller->getSteering(m_character);

    // Check if the steering output is valid.
    if (m_steering.null_output == false)
    {
        // Update the position and orientation
        m_character.setPosition(m_character.getPosition() + m_steering.getVelocity() * dt);
        m_character.setOrientation(m_character.getOrientation() + m_steering.getRotation() * dt);

        // Wrap orientation between [-pi, pi)
        if (m_character.getOrientation() > sf::radians(PI_F)) // char.orient > PI
            m_character.setOrientation(m_character.getOrientation() - sf::radians(2 * PI_F)); // char.orient -= 2*PI
        else if (m_character.getOrientation() < sf::radians(-PI_F)) // char.orient < -PI
            m_character.setOrientation(m_character.getOrientation() + sf::radians(2 * PI_F)); // char.orient += 2*PI

        // std::cout << "sprite.orient = " << m_character.getOrientationFloat() << std::endl;
        
        // Update the sprite position and rotation
        m_sprite.setPosition(m_character.getPosition());
        m_sprite.setRotation(m_character.getOrientation()); // AI-gen: Adjust for sprite facing up
    } else {
        // std::cout << "No Steering behavior" << std::endl;
    }
};

// Helper function to set the Boid texture
void Boid::setTexture(sf::Texture &texture)
{
    m_sprite.setTexture(texture);
};

void Boid::draw(sf::RenderWindow &window)
{
    window.draw(m_sprite);
}