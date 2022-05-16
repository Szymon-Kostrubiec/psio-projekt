#include "characterchoice.hpp"
#include "ui_characterchoice.h"

CharacterChoice::CharacterChoice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CharacterChoice), m_difficulty(Difficulty::Easy)
{
    ui->setupUi(this);
    m_labels = {ui->easy, ui->normal, ui->hard};

    clearButtons();
}

CharacterChoice::~CharacterChoice()
{
    delete ui;
}

void CharacterChoice::on_play_clicked()
{
    this->hide();
    GameMaster game(1000, 800);

    //game setup
    auto health = 750 - 250 * static_cast<uint16_t>(m_difficulty);

    auto hero = std::make_shared<Hero>(500, 300, health);
    game.addObject(hero);
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

