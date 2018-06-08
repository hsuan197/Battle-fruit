#ifndef STARTSCENE_H
#define STARTSCENE_H
#include<QGraphicsScene>
#include<QPushButton>
#include<QTimer>
#include"building.h"
#include"char.h"
#include"btn.h"
#include"enemy.h"
#include<QProgressBar>
#include<QLabel>
#include<sqrat.h>
#include<walk.h>
#include"particle.h"

class StartScene : public QGraphicsScene{

    Q_OBJECT

public:

    //keyboard
    charchoose *charbtn[5];
    QPushButton *towerattack;
    QPushButton *updatebtn;

    //building
    build* p1b2;
    build* p2b2;

    int moneycost[9]={4,4,5,2,2,7,4,7};

    int onboard[8];

    int money = 0;
    int moneyinc = 1;
    int max_money = 30;

    int score;

    int count;
    bool start;

    QTimer *timer;
    QTimer *timer2;
    QTimer *energytimer;
    QLabel *label;

    QPixmap lemon;
    QPixmap strawberry;
    QPixmap pear;
    QPixmap orange;
    QPixmap tomato;
    QPixmap pineapple;
    QPixmap apple;
    QPixmap watermelon;

    HSQUIRRELVM vm;
    Sqrat::Function *update_money;
    Sqrat::Function *update_maxmoney;
    Sqrat::Function *countdown_money;
    Sqrat::Function *addchar_money;

    StartScene();

    void setkeyboard();

    void setonboadbtn();

    void deletonboardbtn();

    void addenemy();

    void setbuilding();

    void addchar(int);

    void setcooseposition(int, int);

    void changebtns();

    void countdown();

    void result();

    void update();

    void towerattackfun();

    void attastart();

    ~StartScene();

signals:
    void win(int);

    void lose();

};

#endif // STARTSCENE_H
