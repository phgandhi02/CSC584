#ifndef BOID_HPP
#define BOID_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Boid {
    public:
        Boid(sf::Texture& texture, float speed, sf::Vector2f startPos);
        void update();
        void draw(sf::RenderWindow& window);
    private:
        sf::Sprite m_sprite;
        sf::Texture& m_texture;
        float m_speed;
        sf::Vector2f m_position;
        int m_spriteState; // 0 = moving right, 1 = moving down, 2 = moving left, 3 = moving up, 4 = stopped
        bool m_stopped;
};

#endif // BOID_HPP