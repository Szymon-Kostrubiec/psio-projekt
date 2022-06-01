#pragma once

#include <QLabel>
#include <QDialog>
#include "Game/gameengine.hpp"
#include "Game/utility.hpp"
#include "displayplayer.h"

namespace Ui {
class CharacterChoice;
}

class CharacterChoice : public QDialog
{
    Q_OBJECT

public:
    explicit CharacterChoice(QWidget *parent = nullptr);
    ~CharacterChoice();

private slots:
    void on_play_clicked();

    void on_easy_clicked();

    void on_normal_clicked();

    void on_hard_clicked();

    void on_left_clicked();

    void on_right_clicked();

private:
    void clearButtons();

    Ui::CharacterChoice *ui;
    Difficulty m_difficulty;
    QList<QPushButton *> m_labels;
    DisplayPlayer * displayPlayer;
};

