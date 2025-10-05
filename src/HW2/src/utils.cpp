#include "../include/utils.hpp"
#include <iostream>

InputHandler::InputHandler(sf::RenderWindow& window)
: m_window(window)
{
};

bool InputHandler::isMouseButtonDown(){
    return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
};

sf::Vector2i InputHandler::getMousePosition(){
    return sf::Mouse::getPosition(m_window);
};

Static InputHandler::update(){
    isMouseButtonDown();
    sf::Vector2i mousePosition = getMousePosition();
    Static target;
    if (isMouseButtonDown()){
        auto targetPos = sf::Vector2f(mousePosition.x, mousePosition.y);
        target = Static(targetPos,sf::degrees(0.f));
        // std::cout << "x: " << targetPos.x << "," << targetPos.y << std::endl;
    } else {
        target = Static();
        target.null_output = true;
    }
    return target; 
};
