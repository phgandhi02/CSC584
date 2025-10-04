#ifndef BOID_HPP
#define BOID_HPP

#include <SFML/Graphics.hpp>

#include "./utils.hpp"
#include "./steering_behavior.hpp"
#include "./steering/kinematic_align.hpp"
#include "./steering/kinematic_arrive.hpp"
#include "./steering/kinematic_flee.hpp"
#include "./steering/kinematic_seek.hpp"
#include "./steering/kinematic_wander.hpp"

#include <iostream>
#include <optional>
#include <memory>

class Boid
{
public:
    // Constructors and destructors
    Boid(const sf::Texture &texture, float speed, sf::Vector2f startPos);
    ~Boid() = default;

    // Basic Obj Functions
    void update(float dt);
    void draw(sf::RenderWindow &window);
    sf::Vector2f getPosition();
    KinematicSteeringOutput getSteering() { return m_steering; }
    bool breadcrumbs_on;
    void setTexture(sf::Texture &texture);

    // Steering Function
    std::unique_ptr<KinematicMovement> m_controller;

private:
    sf::Sprite m_sprite;
    std::optional<Breadcrumbs> m_breadcrumbs;
    std::optional<InputHandler> m_inputHandler;
    float m_speed;
    Static m_character;
    KinematicSteeringOutput m_steering;

    Static m_target;
};

#endif // BOID_HPP