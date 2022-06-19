#include "Text.hpp"

namespace Game {
extern uint32_t globalTime;

AnimatedText::AnimatedText(uint32_t duration, const std::string &text,
                           uint8_t charSize, uint16_t posX, uint16_t posY)
    : Text(text, charSize, posX, posY),
      timeToClear(duration + Game::globalTime),
      posX(posX),
      posY(posY) {
  setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
}

void AnimatedText::gameTick() {
  if (Game::globalTime > timeToClear) {
    setString("");
  }
}

void AnimatedText::addText(const uint32_t duration, const std::string &string) {
  timeToClear = Game::globalTime + duration;
  setString(string);

  // keep position independently of text width
  setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
  setPosition(posX, posY);
}

}  // namespace Game
