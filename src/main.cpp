#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLocale::setDefault(QLocale(QLocale::English, QLocale::Egypt));

    MainWindow w;
    w.show();
    return a.exec();
}
