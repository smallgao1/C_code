#define  _CRT_SECURE_NO_WARNINGS
#include "snack.h"
#include <locale.h>
int main()
{
	//���ñ��ػ���
	setlocale(LC_ALL, "chs");
	srand((unsigned int)time(NULL));
	int ch =  0;
	do
	{
		system("cls");
		Snack snack = { 0 };//����һ����
		gamestart(&snack);
		gamerun(&snack);
		gameover(&snack);
		printf("Want another game?(Y/N)\n");
		ch = getchar();
		while(getchar()!='\n');
	} while (ch == 'Y' || ch == 'y');
	return 0;
}