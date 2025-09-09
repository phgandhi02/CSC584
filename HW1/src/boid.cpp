#include "boid.hpp"

Boid::Boid(sf::Texture &texture, float speed, sf::Vector2f startPos)
    : m_texture(texture), m_speed(speed), m_spriteState(0), m_stopped(false)
{
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_position);
    m_sprite.setRotation(0.f);
}

void Boid::update()
{
    switch (m_spriteState)
    {
    case 0:
        m_sprite.move(sf::Vector2f(m_speed, 0.f));
        if (m_sprite.getPosition().x >= 640 and m_sprite.getPosition().y <= 0){
            m_spriteState = 1; // moving down
            m_sprite.setRotation(90.f);
        }
        break;
    case 1:
        m_sprite.move(sf::Vector2f(0.f, m_speed));
        if (m_sprite.getPosition().x >= 640 and m_sprite.getPosition().y >= 480){
            m_spriteState = 2; // moving left
            m_sprite.setRotation(180.f);
        }
        break;
    case 2:
        m_sprite.move(sf::Vector2f(-m_speed, 0.f));
        if (m_sprite.getPosition().x <= 0 and m_sprite.getPosition().y >= 480){
            m_spriteState = 3; // moving up
            m_sprite.setRotation(270.f);
        }
        break;
    case 3:
        m_sprite.move(sf::Vector2f(0.f, -m_speed));
        if (m_sprite.getPosition().x <= 0 and m_sprite.getPosition().y <= 0){
            m_spriteState = 4; // stopped
            m_sprite.setRotation(0.f);
        }
        break;
    case 4:
        if (m_sprite.getPosition().x <= 0 and m_sprite.getPosition().y <= 0){
            m_spriteState = 4; // stopped
            m_sprite.setRotation(0.f);
            m_stopped = true;
        }
        break;
    default:
        break;
    }
}

void Boid::draw(sf::RenderWindow &window)
{
    if (!m_stopped)
    {
        window.draw(m_sprite);
        std::cout << m_sprite.getPosition().x << " " << m_sprite.getPosition().y << std::endl; // AI generated
    }
}
