#pragma once

#include <QLabel>
#include <QDialog>
#include <Game/gamemaster.hpp>

namespace Ui {
class CharacterChoice;
}

enum class Difficulty: uint8_t {Easy, Medium, Hard};

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

private:
    void clearButtons();

    Ui::CharacterChoice *ui;
    Difficulty m_difficulty;
    QList<QPushButton *> m_labels;
};

