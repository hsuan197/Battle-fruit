function Update_Money(money,max_money){
    money -= max_money/3*2;
    return money;
}

function Update_MaxMoney(max_money){
    return (max_money*2);
}

function Result_Score(HP,money){
    return (HP + money*3);
}

function Countdown_Money(money,moneyinc){
    return (money+moneyinc);
}

function Addchar_Money(money,moneycost){
    return (money-moneycost);
}

function Special_Move_Up(up){
    if(up==10){
        up=0;
    }
    up=up+1;
    return up;

}

function Special_Move(up){
    if(up>5 && up<=10)return 1;
    else return -1;
}
