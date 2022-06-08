#pragma once

#include <SFML/Graphics/Text.hpp>
#include <cstdint>
#include <string>
#include "gameObject.hpp"
#include "managers.h"

namespace Game {

class Text: public sf::Text {
public:
    explicit Text(std::string const &text, uint8_t charSize, uint16_t posX, uint16_t posY) :
        m_font(FontManager::get().getFont("Fonts/Creme.ttf"))
    {
        setPosition(posX, posY);
        setFont(m_font);
        setString(text);
        setCharacterSize(charSize);
        setFillColor(sf::Color::White);
    }
    virtual ~Text() {

    }
    virtual void gameTick() {

    }
private:
    sf::Font m_font;
};

} //namespace game

