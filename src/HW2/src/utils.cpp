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
    image = sf::CircleShape(10.0f);
    image.setPosition(pos.getPosition());
    image.setRotation(pos.getOrientation());
    image.setOutlineThickness(1);
    image.setOutlineColor(sf::Color(250, 150, 100));
};

Breadcrumb::Breadcrumb(Static pos, float radius, float outlineThickness, sf::Color color)
{
    image = sf::CircleShape(radius);
    image.setPosition(pos.getPosition());
    image.setRotation(pos.getOrientation());
    image.setOutlineThickness(outlineThickness);
    image.setOutlineColor(color);
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

    auto initBreadcrumb = Breadcrumb(character, m_radius, m_outlineThickness, m_colors[m_currentColor]);
    m_breadcrumbs = {initBreadcrumb};

    m_numFramesSinceBreadcrumb += 1;
};

void Breadcrumbs::update(Static character)
{
    (m_colors.size() == (m_currentColor - 1))? m_currentColor = 0 : m_currentColor += 1; 

    if (m_numFramesSinceBreadcrumb >= delay && !m_breadcrumbs.empty())
    {
        auto breadcrumb = Breadcrumb(character, m_radius, m_outlineThickness, m_colors[m_currentColor]);
        m_breadcrumbs.push_back(breadcrumb);
        m_numFramesSinceBreadcrumb = 0;
    }

    if (m_numFramesSinceDecay >= decay && !m_breadcrumbs.empty()){
        m_breadcrumbs.erase(m_breadcrumbs.begin());
        m_numFramesSinceDecay = 0;
    }

    m_numFramesSinceBreadcrumb += 1;
    m_numFramesSinceDecay += 1;
}