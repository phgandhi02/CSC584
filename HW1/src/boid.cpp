#include "boid.hpp"

Boid::Boid(sf::Texture& texture, float speed, sf::Vector2f startPos)
    : m_texture(texture), m_speed(speed), m_spriteState(0),m_stopped(false)
{
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_position);
    m_sprite.setRotation(0.f);
}

void Boid::update(){
    if (m_sprite.getPosition().x < 640 and m_sprite.getPosition().y <= 0 and m_spriteState == 0){
        m_spriteState = 0; // moving right
        m_sprite.setRotation(0.f);
    } else if (m_sprite.getPosition().x >= 640 and m_sprite.getPosition().y <= 0 and m_spriteState == 0){
        m_spriteState = 1; // moving down
        m_sprite.setRotation(90.f);
    } else if (m_sprite.getPosition().x >= 640 and m_sprite.getPosition().y >= 480 and m_spriteState == 1){
        m_spriteState = 2; // moving left
        m_sprite.setRotation(180.f);
    } else if (m_sprite.getPosition().x <= 0 and m_sprite.getPosition().y >= 480 and m_spriteState == 2){
        m_spriteState = 3; // moving up
        m_sprite.setRotation(270.f);
    } else if (m_sprite.getPosition().x <= 0 and m_sprite.getPosition().y <= 0 and m_spriteState == 3){
        m_spriteState = 4; // stopped
        m_sprite.setRotation(0.f);
    }


    // Update the sprite position based on its state.
    if (m_spriteState == 0){ // moving right
        m_sprite.move(sf::Vector2f(m_speed, 0.f));
    } else if (m_spriteState == 1){ // moving down
        m_sprite.move(sf::Vector2f(0.f, m_speed));
    } else if (m_spriteState == 2){ // moving left
        m_sprite.move(sf::Vector2f(-m_speed, 0.f));
    } else if (m_spriteState == 3){ // moving up
        m_sprite.move(sf::Vector2f(0.f, -m_speed));
    } else if (m_spriteState == 4){ // stopped
        m_stopped = true;
    }
        
}

void Boid::draw(sf::RenderWindow& window){
    window.draw(m_sprite);
}
