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

class Boid {
    public:
    // Constructors and destructors
        Boid(sf::Texture &texture, float speed, sf::Vector2f startPos);
        ~Boid() = default;
    
    // Basic Obj Functions
        void update();
        void draw(sf::RenderWindow& window);
        sf::Vector2f getPosition();
        bool breadcrumbs_on;

    // Steering Function
        KinematicSteeringOutput align(std::unique_ptr<KinematicMovement> align_steering);
        void arrive(std::unique_ptr<KinematicMovement> arrive_steering);
        void flee(std::unique_ptr<KinematicMovement> flee_steering);
        void seek(std::unique_ptr<KinematicMovement> seek_steering);
        void wander(std::unique_ptr<KinematicMovement> wander_steering);

    private:
        sf::Sprite m_sprite;
        std::optional<Breadcrumbs> m_breadcrumbs;
        std::optional<InputHandler> m_inputHandler;
        sf::Texture m_texture;
        float m_speed; 
        Static m_character;

        Static m_target;
};

#endif // BOID_HPP