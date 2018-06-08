#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QObject::connect(w.quit, &QPushButton::clicked, &a, &QApplication::quit);
    QObject::connect(w.start, &QPushButton::clicked, &w, & MainWindow::gamestart);

    w.show();
    return a.exec();

}
