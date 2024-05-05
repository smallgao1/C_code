#if 0
#define  _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
//设置光标位置
void SetPos(short x, short y)
{
	COORD pos = { x,y };
	HANDLE houtput = NULL;
	houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(houtput, pos);
}
void text01()
{
	system("mode con cols=100 lines=30");
	system("title 贪吃蛇");
	//得到一个控制台输出句柄
	//HANDLE houtput = NULL;
	//houtput=GetStdHandle(STD_OUTPUT_HANDLE);
	// 
	//光标信息结构体
	//CONSOLE_CURSOR_INFO cursorinfo;
	//GetConsoleCursorInfo(houtput,&cursorinfo);
	//cursorinfo.bVisible = false;
	// 
	//设置光标信息
	//SetConsoleCursorInfo(houtput, &cursorinfo);
	//设置光标位置
	//SetPos(20,20);
	// 
	//printf("hehe\n");
	//system("pause");

}
void test02()
{
	/*short ret = GetAsyncKeyState(VK_F1);
	if ((ret & 1) == 1)
	{
		printf("F1按键被按下\n");
	}
	else
	{
		printf("没有按下\n");/utf-8
	}*/

}
int main()
{
	setlocale(LC_ALL,"chs");
	//test01();
	//while (1)
	//{
	//	test02();
	//	Sleep(500);
	//}
	wchar_t ch1 = L'●';
	wchar_t ch2 = L'比';
	wchar_t ch3 = L'特';
	wchar_t ch4 = L'★';

	printf("%c%c\n", 'a', 'b');

	wprintf(L"%lc\n", ch1);
	wprintf(L"%lc\n", ch2);
	wprintf(L"%lc\n", ch3);
	wprintf(L"%lc\n", ch4);

	return 0;
}
#endif