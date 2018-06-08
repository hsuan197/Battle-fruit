#ifndef CHAR_H
#define CHAR_H
#include<QList>
#include<QDebug>
#include<QGraphicsPixmapItem>
#include<QTimer>
#include<sqrat.h>
#include<startscene.h>
#include"enemy.h"
#include"building.h"
#include"walk.h"

class chara :public QObject, public QGraphicsPixmapItem
{

    Q_OBJECT

public:
    chara(int HP,int fig, int num){
        this->HP=HP;
        this->Fig=fig;
        this->num=num;
    }

    int HP;
    int Fig;
    int num;
    int speed =1;
    int delay=0;
    int attackcount=25;

    QList<QGraphicsItem*> collisions;

    void move(){
        if(HP<=0){
                this->~QGraphicsItem();
        }
        int result = *walk[num]->Evaluate<int, int>(x());
        if(num>1)
            this->moveBy(speed, result*speed);
        else
            this->moveBy(result*speed, 0);
    }

    void handleCollisions(){
        if(collidingItems().empty())speed=1;
        else{
            this->collisions= collidingItems();
            foreach (QGraphicsItem *ltem, collisions) {
                enemy *bad = dynamic_cast<enemy *>(ltem);
                if(bad!=NULL){

                    if(bad->HP<=0)this->speed=1;
                    else if(this->HP<=0)bad->speed=1;
                    else{
                        this->speed=0;
                        bad->speed=0;
                    }
                    if(attackcount==50){
                        bad->HP -= Fig;
                        attackcount=0;
                    }
                    else ++attackcount;
                }
                build *building = dynamic_cast<build*>(ltem);
                if(building!=NULL){
                    if(building->HP<=0)speed=1;
                    else speed=0;
                    if(attackcount==50){
                       building->HP-=Fig;
                       attackcount=0;
                    }

                    else ++attackcount;
                }
                chara *fruit = dynamic_cast<chara *>(ltem);
                if(fruit!=NULL){
                   QPixmap juice;
                   juice .load(":/char/9");
                   juice = juice.scaled(50,50);
                   fruit->setPixmap(juice);
                   fruit->HP = ( fruit->HP  + this->HP )*1.2;
                   fruit->Fig = ( fruit->Fig  + this->Fig)*1.2;
                   this->~QGraphicsItem();
                }
            }
        }
    }

    void beattack(){
        foreach (QGraphicsItem *ltem, collisions) {
            enemy *bad = dynamic_cast<enemy *>(ltem);
            if(bad!=NULL){
                if(attackcount==50){
                    this->HP -=bad->Fig;
                }
            }
        }
    }
};

#endif // CHAR_H
