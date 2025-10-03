#include "../include/utils.hpp"
bool InputHandler::wasMouseButtonPressed(){
    return m_isButtonDown && !m_isPrevFrameButtonDown;
}