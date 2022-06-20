#include "displayplayer.h"

const std::array<std::string, 5> DisplayPlayer::playerFileNames{
    "Textures/player1.png", "Textures/player2.png", "Textures/player3.png",
    "Textures/player4.png", "Textures/player5.png"};

DisplayPlayer::DisplayPlayer(QObject *parent)
    : QGraphicsScene{parent}, currentPlayer(0), pixMapDisplayed(nullptr) {
  changePlayer(0);
}

DisplayPlayer::~DisplayPlayer() { delete pixMapDisplayed; }

void DisplayPlayer::changePlayer(int8_t amount) {
  currentPlayer += amount;

  if (currentPlayer < 0)
    currentPlayer = playerTexCount - 1;
  else if (currentPlayer == playerTexCount)
    currentPlayer = 0;

  delete pixMapDisplayed;
  pixMapDisplayed = new QGraphicsPixmapItem(
      QPixmap(QString::fromStdString(playerFileNames.at(currentPlayer))));
  addItem(pixMapDisplayed);
  pixMapDisplayed->setScale(40);
}
