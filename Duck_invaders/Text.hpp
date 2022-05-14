#pragma once

#include <SFML/Graphics/Text.hpp>
#include <cstdint>
#include <string>
#include "gameObject.hpp"

namespace Game {

class Text: public sf::Text {
public:
    explicit Text(std::string const &text);
    virtual ~Text();
    virtual void gameTick();

private:
    std::string text;
};

class TemporaryText: public Text {
public:
    TemporaryText(std::string const &text);
    ~TemporaryText();
    void gameTick() override;

    uint32_t timeToDie;
};

} //namespace game

