#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /*window*/
    setWindowTitle("JUSTICE  LEMON");
    QDesktopWidget wid;
    int screenW = 1000;
    int screenH = 650;
    setGeometry(wid.screen()->width()/2 - (screenW/2) , wid.screen()->height()/2 - (screenH/2) , screenW , screenH);
    setWindowIcon(QIcon(":/other/icon.png"));

    /*init scene*/
    initialscene=new QGraphicsScene() ;
    initialscene->setSceneRect(0,0,1000, 650);

    QImage bg;
    bg.load(":/other/st");
    bg = bg.scaled(1000,650);
    initialscene->setBackgroundBrush(bg);

    start = new QPushButton("START");
    quit = new QPushButton("QUIT");
    QFont btn("Courier", 20, QFont::Bold, false);
    start->setFont(btn);
    start->setGeometry(600,480, 100, 60);
    quit->setFont(btn);
    quit->setGeometry(770,480, 100,60);
    initialscene->addWidget(start);
    initialscene->addWidget(quit);

    /*win scene*/
    winscene = new QGraphicsScene() ;
    winscene->setSceneRect(0,0,1000, 650);

    bg.load(":/other/win");
    bg = bg.scaled(1000,650);
    winscene->setBackgroundBrush(bg);

    winreturn = new QPushButton("RETURN");
    winreturn->setGeometry(50,50,120,60);
    winscene->addWidget(winreturn);
    connect(winreturn, &QPushButton::clicked, this, &MainWindow::initial);

    /*lose scene*/
    losescene=new QGraphicsScene() ;
    losescene->setSceneRect(0,0,1000, 650);

    bg.load(":/other/lose");
    bg = bg.scaled(1000,650);
    losescene->setBackgroundBrush(bg);

    losereturn = new QPushButton("RETURN");
    losereturn->setGeometry(50,50,120,60);
    losescene->addWidget( losereturn);
    connect(losereturn, &QPushButton::clicked, this, &MainWindow::initial);

    /*start*/
    view = new QGraphicsView(initialscene, this);
    setCentralWidget(view);
}

void MainWindow::gamestart(){
    st = new StartScene();
    view->setScene(st);
    QObject::connect(st,&StartScene::win, this, &MainWindow::win);
    QObject::connect(st,&StartScene::lose, this, &MainWindow::lose);
}

void MainWindow::win(int score){
    view->setScene(winscene);
    st->timer->stop();
    st->timer2->stop();
    st->energytimer->stop();
    st->clear();
}

void MainWindow::lose(){
    view->setScene(losescene);
    st->timer->stop();
    st->timer2->stop();
    st->energytimer->stop();
    st->clear();
}

void MainWindow::initial(){
    view->setScene(initialscene);
 }

MainWindow::~MainWindow()
{}
