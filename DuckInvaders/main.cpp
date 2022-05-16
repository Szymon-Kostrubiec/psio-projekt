#include "mainwindow.hpp"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile styleSheetFile(":/style.qss");
    styleSheetFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString styleSheet{QLatin1String(styleSheetFile.readAll())};
    a.setStyleSheet(styleSheet);

    MainWindow w;
    w.show();
    return a.exec();
}
