#include "creditswindow.hpp"
#include "ui_creditswindow.h"

CreditsWindow::CreditsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditsWindow)
{
    ui->setupUi(this);
    setWindowTitle("Credits: Duck Invaders");
}

CreditsWindow::~CreditsWindow()
{
    delete ui;
}
