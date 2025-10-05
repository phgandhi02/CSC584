#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Window.hpp>

#include "./steering_behavior.hpp"

#include <memory>

class InputHandler{
    public:
        InputHandler(sf::RenderWindow& window);
        ~InputHandler() = default;
        bool isMouseButtonDown();
        sf::Vector2i getMousePosition();
        Static update();
    private:
        sf::Vector2i m_mousePosition;
        sf::RenderWindow& m_window;
};

class Breadcrumbs{

};

#endif // UTILS_HPP