#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "../movement/boid.hpp"
#include "../movement/steering_behavior.hpp"
#include <SFML/Graphics.hpp>
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
    GameState() = default;
    GameState(Graph& graph, Boid& enemyCat, Boid& player, sf::Vector2f seedPos, float score)
    {
        m_graph = graph;
        m_enemyCat = CharacterState(enemyCat);
        m_player = CharacterState(player);
        m_seedPos = seedPos;
        m_score = score;
    }
    ~GameState() = default;

    // Game Metric getters
    float getDistance() { return (m_player.getPosition() - m_enemyCat.getPosition()).length(); }
    

    // Game conditional tests
    bool isEnemyTextRect(sf::IntRect textRect) { return (textRect == m_enemyCat.textureRect); }
    bool isPlayerTextRect(sf::IntRect textRect) { return (textRect == m_player.textureRect); }

    // Member Variable getters
    sf::Vector2f getEnemyCatPos() {return m_enemyCat.getPosition();}
    unsigned int getEnemyCatCurrentNode() { return calcNodeIndex(m_enemyCat.getPosition());}
    sf::Vector2f getPlayerPos() {return m_player.getPosition();}
    unsigned int getPlayerCurrentNode() { return calcNodeIndex(m_player.getPosition());}
    sf::Vector2f getSeedPos() {return m_seedPos;}
    unsigned int getSeedCurrentNode() { return calcNodeIndex(m_seedPos);}
    float getScore() { return m_score; }
    std::vector<Connection> getPath(sf::Vector2f startPos, sf::Vector2f endPos);
private:
    Graph m_graph;
    CharacterState m_enemyCat;
    CharacterState m_player;
    sf::Vector2f m_seedPos;
    float m_score;
};

#endif // GAME_STATE_HPP