#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <SFML/System.hpp>

class GameState
{
public:
    GameState(sf::Vector2f enemyCat, sf::Vector2f player, sf::Vector2f seed, float score): 
        m_enemyCatPos(enemyCat), m_playerPos(player), m_seedPos(seed), m_score(score) {};
    ~GameState() = default;
    sf::Vector2f m_enemyCatPos;
    sf::Vector2f m_playerPos;
    sf::Vector2f m_seedPos;
    float m_score;
};

#endif // GAME_STATE_HPP