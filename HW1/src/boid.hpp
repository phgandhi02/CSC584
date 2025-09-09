//  Used Gemini to guide my thinking.
#ifndef BOID_HPP
#define BOID_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Boid {
    public:
        Boid(sf::Texture& texture, float speed, sf::Vector2f startPos);
        void update();
        void draw(sf::RenderWindow& window);
        int getSpriteState() const;
        sf::Vector2f getPosition() const { return m_sprite.getPosition(); }
        void start() { m_started = true; }
        bool isStarted() const { return m_started; }
        bool isStopped() const { return m_stopped; }
    private:
        sf::Sprite m_sprite;
        sf::Texture& m_texture;
        float m_speed;
        sf::Vector2f m_position;
        float m_rotation;
        int m_spriteState; // 0 = moving right, 1 = moving down, 2 = moving left, 3 = moving up, 4 = stopped
        bool m_stopped;
        bool m_started;
};

#endif // BOID_HPP