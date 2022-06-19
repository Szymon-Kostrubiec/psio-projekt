#pragma once

#include <SFML/Graphics/Text.hpp>
#include <cstdint>
#include <string>

#include "gameObject.hpp"
#include "managers.h"

namespace Game {

class Text : public sf::Text {
 public:
  explicit Text(std::string const &text, uint8_t charSize, uint16_t posX,
                uint16_t posY)
      : m_font(FontManager::get().getFont("Fonts/Creme.ttf")) {
    setPosition(posX, posY);
    setFont(m_font);
    setString(text);
    setCharacterSize(charSize);
    setFillColor(sf::Color::White);
    setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
  }
  virtual ~Text() {}
  virtual void gameTick() {}

 private:
  sf::Font m_font;
};

class AnimatedText : public Text {
 public:
  explicit AnimatedText(uint32_t duration, std::string const &text,
                        uint8_t charSize, uint16_t posX, uint16_t posY);

  virtual void gameTick() override;
  void addText(uint32_t const duration, std::string const &string);

 private:
  uint32_t timeToClear{};
  uint16_t posX;
  uint16_t posY;
};

}  // namespace Game
