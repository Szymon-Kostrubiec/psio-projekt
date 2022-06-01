#include "displayplayer.h"

const std::array<std::string, 5> DisplayPlayer::playerFileNames{
    "player1.png", "player2.png", "player3.png", "player4.png", "player5.png"};

DisplayPlayer::DisplayPlayer(QObject *parent) : QGraphicsScene{parent}, pixMapDisplayed(nullptr),
    currentPlayer(0) {

}

DisplayPlayer::~DisplayPlayer()
{
    delete pixMapDisplayed;
}

void DisplayPlayer::changePlayer(int8_t amount)
{
    currentPlayer += amount;

    if (currentPlayer < 0)
        currentPlayer = playerTexCount - 1;
    else if (currentPlayer == playerTexCount)
        currentPlayer = 0;

//    removeItem(pixMapDisplayed);
    delete pixMapDisplayed;
    pixMapDisplayed = new QGraphicsPixmapItem(QPixmap(QString::fromStdString(playerFileNames.at(currentPlayer))));
    addItem(pixMapDisplayed);
}
