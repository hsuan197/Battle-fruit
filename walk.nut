/*walk functions*/
function walk0(a){
	return 1;
}
function walk1(a){
	return (a%3)?1:2;
}

function walk2(a){
	local y = (a-500)*0.004;
	return y;
}
function walk3(a){
	local y = (a%200)>99?1:-1;
	return y;
}
function walk4(a){
	local y = ((a-100)%400)>199? a%2:-a%2;
	return y;
}

/*some money compute functions*/

function Update_Money(money,max_money){
    money -= max_money/3*2;
    return money;
}

function Update_MaxMoney(max_money){
    return (max_money*2);
}

function Countdown_Money(money, moneyinc){
    return (money+moneyinc);
}

function Addchar_Money(money, moneycost){
    return (money-moneycost);
}
