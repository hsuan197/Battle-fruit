#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QMainWindow>
#include<QDesktopWidget>
#include"startscene.h"
#include<QGraphicsView>
#include<QGraphicsScene>
#include"startscene.h"
#include<QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    //Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);

    QPushButton * quit;
    QPushButton * start;

    QPushButton * winreturn;
    QPushButton * losereturn;

    QGraphicsView *view;

    QGraphicsScene*initialscene;
    QGraphicsScene*winscene;
    QGraphicsScene*losescene;

    StartScene *st;

    void initial();

    void gamestart();

    void stacha();

    void win(int);

    void lose();

    ~MainWindow();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
