#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Window.hpp>

#include "./steering_behavior.hpp"

class InputHandler{
    public:
        bool isMouseButtonDown();
        sf::Vector2i getMousePosition() {return sf::Mouse::getPosition();}
        Static update();
    private:
        sf::Vector2i m_mousePosition;
};

class Breadcrumbs{

};

#endif // UTILS_HPP