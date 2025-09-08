#include "boid.hpp"

Boid::Boid(sf::Texture& texture, float speed, sf::Vector2f startPos)
    : m_texture(texture), m_speed(speed), m_spriteState(0),m_stopped(false)
{
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_position);
    m_sprite.setRotation(0.f);
}

void Boid::update(){
    // Define the rest of the logic later
    m_sprite.move(sf::Vector2f(m_speed, 0.f));
}

void Boid::draw(sf::RenderWindow& window){
    window.draw(m_sprite);
}
