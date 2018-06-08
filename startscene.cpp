#include "startscene.h"

StartScene::StartScene(){

    /*squirrel part*/
    vm = sq_open(1024);

    /*run script*/
    Sqrat::Script s(vm);
    s.CompileFile("your squirrel file path");
    s.Run();

    /*money functions*/
    update_money = new Sqrat::Function(Sqrat::RootTable(vm), "Update_Money");
    update_maxmoney = new Sqrat::Function(Sqrat::RootTable(vm), "Update_MaxMoney");
    countdown_money = new Sqrat::Function(Sqrat::RootTable(vm), "Countdown_Money");
    addchar_money = new Sqrat::Function(Sqrat::RootTable(vm), "Addchar_Money");

    /*walk functions*/
    int a;
    for(a=0; a<5; a++){
        char name[6]="walk";
        name[4] = a + '0';
        walk[a] = new Sqrat::Function(Sqrat::RootTable(vm), name);
        if(walk[a]->IsNull()){
            qDebug()<<"QQ";
        }
    }

    /*background*/
    this->setSceneRect(0,0,1000, 650);
    QImage bg;
    bg.load(":/other/bg");
    bg = bg.scaled(1000,650);
    this->setBackgroundBrush(bg);
    score = 0;

    /*character pictures*/
    lemon.load(":/char/1");
    lemon = lemon.scaled(50,50);
    strawberry.load(":/char/2");
    strawberry = strawberry.scaled(50,50);
    pear .load(":/char/3");
    pear = pear.scaled(50,50);
    orange .load(":/char/4");
    orange = orange.scaled(50,50);
    tomato .load(":/char/5");
    tomato = tomato.scaled(50,50);

    /*timers*/
    timer = new QTimer(this);
    timer->start(20);
    timer2 = new QTimer(this);
    timer2->start(3000);
    QObject::connect( timer2, &QTimer::timeout, this, &StartScene::addenemy);
    QObject::connect( timer, &QTimer::timeout, this, &StartScene::result);
    QObject::connect( timer, &QTimer::timeout, this, &StartScene::towerattackfun);

    /*energy*/
    energytimer = new QTimer(this);
    energytimer->start(500);
    QObject::connect( energytimer, &QTimer::timeout, this, &StartScene::countdown);

    /*items*/
    setonboadbtn();
    setbuilding();

    /*money show*/
    label = new QLabel;
    label->setGeometry(650, 50, 200, 50);

    QFont lab("Courier", 20, QFont::Bold, false);
    label->setFont(lab);
    label->setText(QString::number(money)+" / "+QString::number(max_money)+" ");
    //label->setStyleSheet("background:transparent");
    label->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    this->addWidget(label);

    /*updatebtn*/
    updatebtn = new QPushButton;
    updatebtn->setGeometry(10, 450, 100, 100);

    QFont btn("Courier", 16, QFont::Bold, false);
    updatebtn->setFont(btn);
    updatebtn->setText("update \n("+QString::number(max_money/3*2)+")");

    QObject::connect(updatebtn, &QPushButton::clicked, this, &StartScene::update);
    this->addWidget(updatebtn);

    /*tower attack btn*/
    towerattack = new QPushButton;
    towerattack->setGeometry(890, 450, 100, 100);

    towerattack->setFont(btn);
    towerattack->setText("Attack\n(30)");

    QObject::connect( towerattack, &QPushButton::clicked, this, &StartScene::attastart);
    this->addWidget(towerattack);
}

void StartScene::setonboadbtn(){
    int a;
    for(a=0; a<5; ++a){
        charbtn[a] = new charchoose (a);
        charbtn[a]->btn=new QPushButton();
        charbtn[a]->btn->setGeometry(a*150 + 150, 450, 100, 100);

        this->addWidget(charbtn[a]->btn);
        QObject::connect(charbtn[a]->btn, &QPushButton::clicked,charbtn[a],&charchoose::click);
        QObject::connect(charbtn[a], &charchoose::changechoosechar,this,&StartScene::addchar);
        switch (a) {
            case 0:    charbtn[a]->btn-> setStyleSheet("background-image:url(:/btn/1)"); break;
            case 1:    charbtn[a]->btn-> setStyleSheet("background-image:url(:/btn/2)"); break;
            case 2:    charbtn[a]->btn-> setStyleSheet("background-image:url(:/btn/3)"); break;
            case 3:    charbtn[a]->btn-> setStyleSheet("background-image:url(:/btn/4)"); break;
            case 4:    charbtn[a]->btn-> setStyleSheet("background-image:url(:/btn/5)"); break;
            case 5:    charbtn[a]->btn-> setStyleSheet("background-image:url(:/btn/6)"); break;
            case 6:    charbtn[a]->btn-> setStyleSheet("background-image:url(:/btn/7)"); break;
            case 7:    charbtn[a]->btn-> setStyleSheet("background-image:url(:/btn/8)"); break;
            default: break;
        }
    }
}

void StartScene::countdown(){
    if(money+moneyinc>max_money)
        return;
    money = *countdown_money->Evaluate<int, int>(money, moneyinc);
    label->setText(QString::number(money)+" / "+QString::number(max_money)+" ");
}

void StartScene::addchar(int kind){
    if(moneycost[kind] <= money){
        int hp, fig;
        QPixmap addfruit;
        switch (kind) {
            case 0: addfruit = lemon; hp = 2500; fig = 100;break;
            case 1: addfruit = strawberry; hp = 1500; fig = 120;break;
            case 2: addfruit = pear; hp = 4000; fig = 60;break;
            case 3: addfruit = orange; hp = 1000; fig = 100;break;
            case 4: addfruit = tomato; hp = 1100; fig = 80;break;
            default: return;
        }
        chara *newfruit= new chara(hp, fig, kind);

        money = *addchar_money->Evaluate<int, int>(money, moneycost[kind]);

        newfruit->setPixmap(addfruit);
        newfruit->setPos(150, 250);
        this->addItem(newfruit);

        QObject::connect( timer, &QTimer::timeout, newfruit, &chara::move);
        QObject::connect( timer, &QTimer::timeout, newfruit, &chara::handleCollisions);
        QObject::connect( timer, &QTimer::timeout, newfruit, &chara::beattack);

        label->setText(QString::number(money)+" / "+QString::number(max_money)+" ");
    }
}

void StartScene::setbuilding(){
    p1b2= new build(3000);
    QPixmap b2;
    b2.load(":/bui/b2");
    b2 = b2.scaled(150,200);
    p1b2->setPixmap(b2);
    p1b2->setPos(0,150);
    connect(timer,&QTimer::timeout,p1b2,&build::check);
    this->addItem(p1b2);

    p2b2= new build(3000);
    QPixmap eb2;
    eb2.load(":/bui/eb2");
    eb2 = eb2.scaled(150,200);
    p2b2->setPixmap(eb2);
    p2b2->setPos(850,150);
    connect(timer,&QTimer::timeout,p2b2,&build::check);
    this->addItem(p2b2);
}

void StartScene::addenemy(){
    int HP=800, fig=100;

    enemy *bad = new enemy(HP,fig);
    QPixmap ene;
    ene.load(":/bad/ch1-1");
    ene = ene.scaled(50,50);

    bad->setPixmap(ene);
    bad->setPos(800, 250);

    this->addItem(bad);

    QObject::connect( timer, &QTimer::timeout, bad, &enemy::move);
    QObject::connect( timer, &QTimer::timeout, bad, &enemy::handleCollisions);
}

void StartScene::result(){
    if(p2b2->HP <= 0){
        score = p1b2->HP + money*3;
        emit win(score);
    }
    else if(p1b2->HP <= 0){
        emit lose();
    }
}

void StartScene::update(){
    if(money >= max_money/3*2 && max_money < 120){

        money = *update_money->Evaluate<int, int>(money, max_money);
        max_money = *update_maxmoney->Evaluate<int>(max_money);

        energytimer->setInterval(energytimer->interval()-100);
        updatebtn->setText("update \n"+QString::number(max_money/3*2));
    }
}

void StartScene::towerattackfun(){
    if(!start)
        return;
    if(count%8 == 0){
        particle* par = new particle();
        QPixmap p;
        p.load(":/other/particle");
        p.scaled(25, 25);
        par->setPixmap(p);
        par->setPos(150, 250);
        this->addItem(par);
        QObject::connect( timer, &QTimer::timeout, par, &particle::move);
        QObject::connect( timer, &QTimer::timeout, par, &particle::handleCollisions);
    }
    if (count > 100){
        start = false;
    }
    count += 1;
}

void StartScene::attastart(){
    if(money > 29){
        money -= 30;
        start = true;
        count = 0;
        label->setText(QString::number(money)+" / "+QString::number(max_money)+" ");
    }
}

StartScene::~StartScene(){
    sq_close(vm);
}
