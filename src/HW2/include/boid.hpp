#ifndef BOID_HPP
#define BOID_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include "./utils.hpp"
#include "./steering_behavior.hpp"

class Boid {
    public:
        Boid(sf::Texture& texture, float speed, sf::Vector2f startPos);
        void update();
        void draw(sf::RenderWindow& window);
        sf::Vector2f getPosition();
        bool breadcrumbs_on;
    private:
        sf::Sprite m_sprite;
        std::optional<Breadcrumbs> m_breadcrumbs;
        std::optional<InputHandler> m_inputHandler;
        sf::Texture m_texture;
        float m_speed; 
        Static m_character;
        sf::Vector2f m_position;
        float m_rotation;
};

#endif // BOID_HPP