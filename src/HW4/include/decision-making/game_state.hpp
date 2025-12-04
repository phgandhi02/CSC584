#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <SFML/System.hpp>

class CharacterState
{
public:
    CharacterState() = default;
    CharacterState(Boid& boid) {
        character = boid.getCharacter();
        textureRect = boid.getTextureRect();
        target = boid.getTarget();
        steeringOutput = boid.getSteering();
    }
    ~CharacterState() = default;
    sf::Vector2f getPosition() { return character.getPosition(); }
    Static character;
    sf::IntRect textureRect;
    Static target;
    KinematicSteeringOutput steeringOutput;
};

class GameState
{
public:
    GameState(Boid& enemyCat, Boid& player, Boid seed, float score)
    {
        m_enemyCat = CharacterState(enemyCat);
        m_player = CharacterState(player);
    }
    ~GameState() = default;
    CharacterState m_enemyCat;
    CharacterState m_player;
    sf::Vector2f m_seedPos;
    float m_score;
};

#endif // GAME_STATE_HPP