#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Window.hpp>

#include "./steering_behavior.hpp"
// #include "./boid.hpp"

#include <memory>

class InputHandler
{
public:
    InputHandler(sf::RenderWindow &window);
    ~InputHandler() = default;
    bool isMouseButtonDown();
    sf::Vector2i getMousePosition();
    Static update();

private:
    sf::Vector2i m_mousePosition;
    sf::RenderWindow &m_window;
};

class Breadcrumb
{
public:
    Breadcrumb(Static pos);
    Breadcrumb(Static pos, float radius, float outlineThickness, sf::Color color);
    ~Breadcrumb() = default;
    sf::CircleShape image;
};

class Breadcrumbs
{
public:
    Breadcrumbs(Static character, float delay);
    ~Breadcrumbs() = default;
    // number of frames between each breadcrumb
    int delay = 50;
    int decay = 200;
    void update(Static character);
    std::vector<Breadcrumb> m_breadcrumbs;

private:
    int m_numFramesSinceBreadcrumb;
    int m_numFramesSinceDecay;
    std::vector<sf::Color> m_colors; 
    int m_currentColor;
    float m_radius = 2.0f;
    float m_outlineThickness = 2.0f;
};

#endif // UTILS_HPP