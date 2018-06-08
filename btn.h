#ifndef BTN_H
#define BTN_H
#include<QObject>
#include<QPushButton>

class charchoose : public QObject
{
    Q_OBJECT

public:
    charchoose(int num){
        this->num = num;
    }

    QPushButton *btn;

    void click( ){
        emit changechoosechar(num);
    }

private:
    int num;

signals:
    void  changechoosechar(int num);
};




#endif // BTN_H
