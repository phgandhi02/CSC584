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
    Breadcrumb(Static pos, sf::Color color);
    ~Breadcrumb() = default;
    Static breadcrumb;
    sf::CircleShape image;
};

class Breadcrumbs
{
public:
    Breadcrumbs(Static character, float delay);
    ~Breadcrumbs() = default;
    // number of frames between each breadcrumb
    int delay = 500;
    void update(Static character);

private:
    int m_numFramesSinceBreadcrumb;
    std::vector<Breadcrumb> m_breadcrumbs;
    std::vector<sf::Color> m_colors; 
    int m_currentColor;
};

#endif // UTILS_HPP