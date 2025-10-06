#include "../include/utils.hpp"

#include <iostream>

/* ------------------------------ InputHandler ------------------------------ */
InputHandler::InputHandler(sf::RenderWindow &window)
    : m_window(window) {
      };

bool InputHandler::isMouseButtonDown()
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
};

sf::Vector2i InputHandler::getMousePosition()
{
    return sf::Mouse::getPosition(m_window);
};

Static InputHandler::update()
{
    isMouseButtonDown();
    sf::Vector2i mousePosition = getMousePosition();
    Static target;
    if (isMouseButtonDown())
    {
        auto targetPos = sf::Vector2f(mousePosition.x, mousePosition.y);
        target = Static(targetPos, sf::degrees(0.f));
        // std::cout << "x: " << targetPos.x << "," << targetPos.y << std::endl;
    }
    else
    {
        target = Static();
        target.null_output = true;
    }
    return target;
};

/* ------------------------------- Breadcrumb ------------------------------- */
Breadcrumb::Breadcrumb(Static pos)
{
    breadcrumb = pos;
    image = sf::CircleShape(10.0f);
    image.setOutlineThickness(1);
    image.setOutlineColor(sf::Color(250, 150, 100));
};

Breadcrumb::Breadcrumb(Static pos, sf::Color color)
{
    breadcrumb = pos;
    image = sf::CircleShape(10.0f);
    image.setOutlineThickness(1);
    image.setOutlineColor(sf::Color(250, 150, 100));
};

Breadcrumbs::Breadcrumbs(Static character, float delay)
{
    m_numFramesSinceBreadcrumb = 0;
    m_colors = {
        sf::Color::Black,
        sf::Color::Blue,
        sf::Color::Cyan,
        sf::Color::Green,
        sf::Color::Magenta,
        sf::Color::Red,
        sf::Color::Yellow};
    m_currentColor = 0;

    auto initBreadcrumb = Breadcrumb(character, m_colors[m_currentColor]);
    m_breadcrumbs = {initBreadcrumb};

    m_numFramesSinceBreadcrumb += 1;
};

void Breadcrumbs::update(Static character)
{
    if (m_colors.size() == (m_currentColor - 1))
    {
        m_currentColor = 0;
    }
    else
    {
        m_currentColor += 1;
    }
    if (m_numFramesSinceBreadcrumb >= 500 && !m_breadcrumbs.empty())
    {
        m_numFramesSinceBreadcrumb = 0;
        m_breadcrumbs.erase(m_breadcrumbs.begin());
        auto breadcrumb = Breadcrumb(character,m_colors[m_currentColor]);
        m_breadcrumbs.push_back(breadcrumb);
        m_numFramesSinceBreadcrumb += 1;
    }
    m_numFramesSinceBreadcrumb += 1;
}