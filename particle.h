#ifndef PARTICLE_H
#define PARTICLE_H
#include<QList>
#include<QDebug>
#include<QGraphicsPixmapItem>
#include"enemy.h"
#include"building.h"
#include"walk.h"

class particle :public QObject, public QGraphicsPixmapItem
{

    Q_OBJECT

public:
    int attackcount;

    QList<QGraphicsItem*> collisions;

    void move(){
        this->moveBy(3, 0);
    }

    void handleCollisions(){
        if(collidingItems().empty());
        else{
            this->collisions= collidingItems();
            foreach (QGraphicsItem *ltem, collisions) {
                enemy *bad = dynamic_cast<enemy *>(ltem);
                if(bad!=NULL){
                    bad->HP = 0;
                    this->~QGraphicsItem();
                }
                build *building = dynamic_cast<build*>(ltem);
                if(building!=NULL){
                    building->HP -= 10;
                    this->~QGraphicsItem();
                }
            }
        }
    }
};
#endif // PARTICLE_H
