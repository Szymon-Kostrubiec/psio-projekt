#pragma once

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMap>
#include <QObject>

static constexpr uint8_t playerTexCount = 5;

class DisplayPlayer : public QGraphicsScene {
  Q_OBJECT
public:
  explicit DisplayPlayer(QObject *parent = nullptr);
    ~DisplayPlayer();
  std::string getCurrent() { return playerFileNames.at(currentPlayer); }
  void changePlayer(int8_t amount);

private:
  static const std::array<std::string, playerTexCount> playerFileNames;
  int8_t currentPlayer;
  QGraphicsPixmapItem * pixMapDisplayed;
};
