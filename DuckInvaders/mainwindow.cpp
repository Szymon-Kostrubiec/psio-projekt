#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), creditsWindow(new CreditsWindow()), characterChoice(new CharacterChoice())
{
    ui->setupUi(this);
    setWindowTitle("Duck Invaders");

}

MainWindow::~MainWindow()
{
    delete ui;
    delete creditsWindow;
    delete characterChoice;
}

void MainWindow::on_exit_clicked()
{
    QCoreApplication::quit();
}

void MainWindow::on_credits_clicked()
{
    creditsWindow->exec();
}

void MainWindow::on_play_clicked()
{
    this->hide();
    characterChoice->exec();
    this->show();
}

