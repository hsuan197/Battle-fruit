#ifndef ENEMY_H
#define ENEMY_H
#include<QGraphicsPixmapItem>
#include<QList>
#include"building.h"

class enemy :public QObject, public QGraphicsPixmapItem//,public item
{

    Q_OBJECT

public:
    enemy(int HP,int fig){
        this->HP=HP;
        this->Fig=fig;
    }

    int HP;
    int Fig;
    int speed =1;
    int delay=0;

    int attackcount=50;

    QList<QGraphicsItem*> collisions;

    void move(){
        this->moveBy(-speed,0);
        if(HP<=0){
            if(delay==2){
            this->~QGraphicsItem();
            delay=0;
            }
            else ++delay;
        }
    }

    void handleCollisions(){
        this->collisions= collidingItems();
        if(collidingItems().empty())speed=1;
        foreach (QGraphicsItem *ltem, collisions) {
            build *building = dynamic_cast<build*>(ltem);
            if(building!=NULL){
                if(building->HP<=0)speed=1;
                else speed=0;
                if(attackcount >= 50){
                    building->HP-=Fig;
                    attackcount=0;
                }
                else ++attackcount;
            }

            enemy *bad = dynamic_cast<enemy *>(ltem);
            if(bad!=NULL){
                this->~QGraphicsItem();
                bad->HP+=this->HP;
                bad->Fig+=this->Fig;
            }
        }
    }


};
#endif
