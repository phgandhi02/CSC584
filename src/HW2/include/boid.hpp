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
    Boid(Boid&& other) = default; // move constructor

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
    std::unique_ptr<KinematicMovement> controller;
    bool mouseInputOff = true;
    Breadcrumbs breadcrumbs;

private:
    sf::Sprite m_sprite;
    InputHandler m_inputHandler;
    Static m_character;
    KinematicSteeringOutput m_steering;

    Static m_target;
    unsigned int m_windowSizeX = 800;
    unsigned int m_windowSizeY = 600;
};

#endif // BOID_HPP