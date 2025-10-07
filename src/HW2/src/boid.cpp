#include "../include/boid.hpp"
#include "../include/steering/kinematic_flee.hpp"
#include <iostream>

const float PI_F = 3.14159265358979f;

Boid::Boid(const sf::Texture &texture, Static startPos, sf::RenderWindow& window)
    : m_sprite(texture), m_inputHandler(window), m_breadcrumbs(startPos, 100)
{
    m_sprite.setPosition(startPos.getPosition());
    m_sprite.setRotation(startPos.getOrientation());
    breadcrumbs_on = true;
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

    if (!mouseInputOff)
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
        const bool left_collision = 0 > m_character.getPosition().x;
        const bool right_collision =  m_character.getPosition().x > m_windowSizeX;
        const bool up_collision = 0 > m_character.getPosition().y;
        const bool down_collision =  m_character.getPosition().y > m_windowSizeY;

        auto boid_pos = m_character.getPosition();
        auto boid_orient = m_character.getOrientation();

        if ((left_collision | right_collision | up_collision | down_collision)) {
            auto flee_behavior = KinematicFlee();
            if (left_collision) {
                flee_behavior.target = Static(sf::Vector2f(boid_pos.x,boid_pos.y),sf::degrees(0.0f));
            } else if (right_collision) {
                flee_behavior.target = Static(sf::Vector2f(boid_pos.x,boid_pos.y),sf::degrees(180.0f));
            } else if (up_collision) {
                flee_behavior.target = Static(sf::Vector2f(boid_pos.x,boid_pos.y),sf::degrees(90.0f));
            } else if (down_collision) {
                flee_behavior.target = Static(sf::Vector2f(boid_pos.x,boid_pos.y),sf::degrees(-90.0f));
            }
            m_steering = flee_behavior.getSteering(m_character);
        }
        // Update the position and orientation
        m_character.setPosition(boid_pos + m_steering.getVelocity() * dt);
        m_character.setOrientation(boid_orient + m_steering.getRotation() * dt);

        // Wrap orientation between [-pi, pi)
        if (boid_orient > sf::radians(PI_F)) // char.orient > PI
            m_character.setOrientation(boid_orient - sf::radians(2 * PI_F)); // char.orient -= 2*PI
        else if (boid_orient < sf::radians(-PI_F)) // char.orient < -PI
            m_character.setOrientation(boid_orient + sf::radians(2 * PI_F)); // char.orient += 2*PI

        // std::cout << "sprite.orient = " << m_character.getOrientationFloat() << std::endl;
        // std::cout << boid_pos.x << " | " << boid_pos.y << std::endl;
        
        // Update the sprite position and rotation
        m_sprite.setPosition(boid_pos);
        m_sprite.setRotation(boid_orient); // AI-gen: Adjust for sprite facing up
    } else {
        // std::cout << "No Steering behavior" << std::endl;
    }
    if (breadcrumbs_on){
        m_breadcrumbs.update(m_character);
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
    m_windowSizeX = window.getSize().x;
    m_windowSizeY = window.getSize().y;

    // std::cout << m_windowSizeX << " | " << m_windowSizeY << std::endl;

    for (Breadcrumb crumb : m_breadcrumbs.m_breadcrumbs){
        window.draw(crumb.image);
    }
}