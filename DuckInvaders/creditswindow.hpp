#pragma once

#include <QDialog>

namespace Ui {
class CreditsWindow;
}

class CreditsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CreditsWindow(QWidget *parent = nullptr);
    ~CreditsWindow();

private:
    Ui::CreditsWindow *ui;
};

