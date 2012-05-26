#include "ui_fonctions.h"

void showMoney(int money)
{
	char str[10] = {0};
	int i = 0;
	
	intToStr(str, money);
	
	for(i = 0; str[i] != 0; i++)
	{}
	str[i] = '$';
	
	ML_rectangle(90, 45, 125, 55, 1, BLACK, WHITE);
	PrintMini(95, 48, str, MINI_OVER);
}
