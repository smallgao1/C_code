#define  _CRT_SECURE_NO_WARNINGS
#include "snack.h"
#include <locale.h>
int main()
{
	//设置本地环境
	setlocale(LC_ALL, "chs");
	srand((unsigned int)time(NULL));
	int ch =  0;
	do
	{
		system("cls");
		Snack snack = { 0 };//创造一个蛇
		gamestart(&snack);
		gamerun(&snack);
		gameover(&snack);
		printf("Want another game?(Y/N)\n");
		ch = getchar();
		while(getchar()!='\n');
	} while (ch == 'Y' || ch == 'y');
	return 0;
}