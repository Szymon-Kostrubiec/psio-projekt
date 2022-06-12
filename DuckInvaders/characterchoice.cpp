#include "characterchoice.hpp"
#include "ui_characterchoice.h"

CharacterChoice::CharacterChoice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CharacterChoice), m_difficulty(Difficulty::Easy), displayPlayer(new DisplayPlayer())
{
    ui->setupUi(this);
    m_labels = {ui->easy, ui->normal, ui->hard};

    setWindowTitle("Duck Invaders: Choose your hero");

    clearButtons();
    ui->viewPlayer->setScene(displayPlayer);
}

CharacterChoice::~CharacterChoice()
{
    delete ui;
    delete displayPlayer;
}

void CharacterChoice::on_play_clicked()
{
    this->hide();
    GameEngine game(1000, 800, m_difficulty, displayPlayer->getCurrent());
    game.enterGameLoop();
    this->show();
}


void CharacterChoice::on_easy_clicked()
{
    m_difficulty = Difficulty::Easy;
    clearButtons();
}


void CharacterChoice::on_normal_clicked()
{
    m_difficulty = Difficulty::Medium;
    clearButtons();
}


void CharacterChoice::on_hard_clicked()
{
    m_difficulty = Difficulty::Hard;
    clearButtons();
}

void CharacterChoice::clearButtons()
{
    std::for_each(m_labels.begin(), m_labels.end(), [](QPushButton * btn){
        btn->setStyleSheet("color: black;");
    });
    m_labels.at(static_cast<uint8_t>(m_difficulty))->setStyleSheet("color: white;");
}


void CharacterChoice::on_left_clicked()
{
    displayPlayer->changePlayer(-1);
}


void CharacterChoice::on_right_clicked()
{
    displayPlayer->changePlayer(1);
}

