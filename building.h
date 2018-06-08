#ifndef BUILDING_H
#define BUILDING_H
#include<QTimer>
#include<QGraphicsPixmapItem>
#include<QDebug>
class build :public QObject, public QGraphicsPixmapItem
{

    Q_OBJECT

public:
    build(int HP){
        this->HP = HP;
    }

    int HP;
    int delay=0;

    void check(){
        if(HP <= 0){
            if(delay == 2){
                this->~QGraphicsItem();
                delay=0;
            }
            else ++delay;
        }
    }

    void towerattack(){
        qDebug()<<"a";
    }

};
#endif // BUILDING_H
