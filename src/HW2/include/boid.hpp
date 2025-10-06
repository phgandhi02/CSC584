#ifndef BOID_HPP
#define BOID_HPP

#include <SFML/Graphics.hpp>

#include "./utils.hpp"
#include "./steering_behavior.hpp"


#include <iostream>
#include <optional>
#include <memory>

class Boid
{
public:
    // Constructors and destructors
    Boid(const sf::Texture &texture, Static startPos, sf::RenderWindow& window);
    ~Boid() = default;

    // Basic Obj Functions
    void update(float dt);
    void draw(sf::RenderWindow &window);
    Static getCharacter() { return m_character; }
    KinematicSteeringOutput getSteering() { return m_steering; }
    bool breadcrumbs_on = true;
    void setTexture(sf::Texture &texture);
    

    // Steering Function
    float speed = 100.0f;
    float smoothing = 0.2f;
    std::unique_ptr<KinematicMovement> m_controller;

private:
    sf::Sprite m_sprite;
    Breadcrumbs m_breadcrumbs;
    InputHandler m_inputHandler;
    Static m_character;
    KinematicSteeringOutput m_steering;

    Static m_target;
    unsigned int m_windowSizeX;
    unsigned int m_windowSizeY;

    bool unittesting = false;
};

#endif // BOID_HPP