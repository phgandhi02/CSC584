#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Window.hpp>

class InputHandler{
    public:
        void update();
        void handleEvent(const sf::Event& event); // call this every frame for each event from the event loop
        void isMouseButtonDown();
        sf::Vector2i getMousePosition() {return sf::Mouse::getPosition();}
    private:
        bool wasMouseButtonPressed();
        bool m_isButtonDown = false;
        bool m_isPrevFrameButtonDown = false;
        sf::Vector2i m_mousePosition;
};

class Breadcrumbs{

};

#endif // UTILS_HPP