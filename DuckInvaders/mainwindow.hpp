#pragma once

#include <QMainWindow>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "creditswindow.hpp"
#include "characterchoice.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_exit_clicked();

    void on_credits_clicked();

    void on_play_clicked();

private:
    Ui::MainWindow *ui;
    CreditsWindow * creditsWindow;
    CharacterChoice * characterChoice;
};
