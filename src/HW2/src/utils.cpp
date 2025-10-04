#include "../include/utils.hpp"
bool InputHandler::isMouseButtonDown(){
    return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
};

Static InputHandler::update(){
    isMouseButtonDown();
    getMousePosition();
    Static target;
    if (isMouseButtonDown()){
        auto targetPos = sf::Vector2f(getMousePosition().x, getMousePosition().y);
        target = Static(targetPos,sf::degrees(0.f));
    } else {
        target = Static();
        target.null_output = true;
    }
    return target; 
};
