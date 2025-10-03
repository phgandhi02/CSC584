#include "../include/boid.hpp"

Boid::Boid(sf::Texture& texture, float speed, sf::Vector2f startPos)
    : m_texture(texture), m_sprite(texture)
{
    m_sprite.setPosition(m_position);
    m_sprite.setRotation(sf::radians(0.0f));
}

void Boid::update()
{
    m_sprite.move(sf::Vector2f(20,0));
};