#include "snack.h"

void SetPos(short x, short y)
{
	COORD pos = { x,y };
	HANDLE houtput = NULL;
	houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(houtput, pos);
}
void disdisplayInfo()
{
	//得到一个控制台输出句柄
	HANDLE houtput = NULL;
	houtput=GetStdHandle(STD_OUTPUT_HANDLE);
	 
	//光标信息结构体
	CONSOLE_CURSOR_INFO cursorinfo;
	GetConsoleCursorInfo(houtput,&cursorinfo);
	cursorinfo.bVisible = false;
	 
	//设置光标信息
	SetConsoleCursorInfo(houtput, &cursorinfo);
}
void printexplanation()
{
	SetPos(20, 17);
	wprintf(L"%ls\n",L"欢迎来到贪吃蛇小游戏");
	SetPos(20, 20);
	system("pause");
	system("cls");//清屏
	SetPos(20, 15);
	wprintf(L"%ls\n", L"用 ↑ . ↓ . ← . → 分别控制蛇的移动， F3为加速，F4为减速");
	SetPos(20, 17);
	printf(L"%ls\n", L"加速将能得到更高的分数");
	SetPos(20, 20);
	system("pause");
	system("cls");//清屏
}
void creatmap()
{
	int i = 0;
	system("mode con cols=100 lines=30");
	SetPos(0, 0);
	for (i = 0; i < 58; i+=2)
	{
		wprintf(L"%lc", L'□');
	}
	SetPos(0, 26);
	for (i = 0; i < 58; i+=2)
	{
		wprintf(L"%lc", L'□');
	}
	for (i = 1; i < 26; i++)
	{
		SetPos(0, i);
		wprintf(L"%lc", L'□');
	}
	for (i = 1; i < 26; i++)
	{
		SetPos(56, i);
		wprintf(L"%lc", L'□');
	}
	SetPos(20, 28);
}
//
void printhelpinfo()
{
	SetPos(62, 17);
	wprintf(L"%ls\n", L"不能穿墙，不能咬到自己");
	SetPos(62, 18);
	wprintf(L"%ls\n", L"用 ↑ . ↓ . ← . → 分别控制蛇的移动");
	SetPos(62, 19);
	wprintf(L"%ls\n", L"F3为加速，F4为减速");
	SetPos(62, 20);
	wprintf(L"%ls\n", L"ESC:退出游戏 SPACE:暂停游戏");
	SetPos(62, 22);
	wprintf(L"%ls\n", L"smallgao@版权");
}
/*
* @brief 创建蛇的节点
* @param x y
* @retval 返回指向该节点的指针
*/
psnacknode creatsnacknode(int x, int y)
{
	psnacknode ps = (psnacknode)malloc(sizeof(snacknode));
	if (ps == NULL)
	{
		perror("creatsnacknode malloc :");
		return NULL;
	}
	ps->x = x;
	ps->y = y;
	ps->next = NULL;
	return ps;
}

/*
* @brief 头插蛇身节点
* @param 蛇身头部指针的指针 , 坐标
* @retval 无
*/
void pushsnacknodefront(psnacknode* pphead,int x,int y)
{
	psnacknode pc = creatsnacknode(x,y);
	pc->next = *pphead;
	*pphead = pc;
}

/*
* @brief 打印蛇身
* @param 蛇的头节点
* @retval 无
*/
void printsnack(psnacknode phead)
{
	psnacknode pcur = phead;
	while (pcur)
	{

		SetPos(pcur->x, pcur->y);
		wprintf(L"%lc", L'●');
		pcur = pcur->next;
	}
}
void snackinit(psnack ps)
{
	printhelpinfo();//打印帮助界面
	//初始化蛇身初始时有5个节点
	for (int i = 0; i < 5; i++)//5行24列
	{
		pushsnacknodefront(&(ps->phead),POS_X+i*2,POS_y);
	}
	ps->direction = RIGHT;
	ps->foodscore = 10;
	ps->score = 0;
	ps->gamestatus = NORMAL;
	ps->sleeptime = 250;
	//打印蛇身
	printsnack(ps->phead);
}

/*
* @brief 创建食物 创建一个节点存放食物坐标并打印“*”
* @param snack型结构体
* 
*/
void creatfood(psnack ps)
{
	//食物要随机生成  
	int x = 0;
	int y = 0;
repeat:

	x = rand()%53+2; //范围 x 2 <= x <= 54 x为偶数
	x = (x % 2 == 0 ? x : x + 1);
	y = rand() % 24 + 1;	//y  1<= y <=25
	//食物不能与蛇身重合
	//遍历蛇身然后goto
	psnacknode pcur =ps->phead;
	while (pcur)
	{
		if (pcur->x == x && pcur->y == y)
		{
			goto repeat;
		}
		pcur = pcur->next;
	}
	pushsnacknodefront(&(ps->pfood), x, y);//直接头插2
	SetPos(x,y);
	if (x == 2 || x == 54 || y == 1 || y == 25)
	{
		wprintf(L"%lc", L'▲');
		ps->foodscore = 12;
	}
	else if ((x>=2&&x<52)&&((y>=1&&y<=4)||(y>=22&&y<=25)))
	{
		wprintf(L"%lc", L'□');
		ps->foodscore = 10;
	}
	else if ( ((x >= 1 && x <=8)|| (x >= 48 && x <=54))&&(y >= 5 && y <= 21) )
	{
		wprintf(L"%lc", L'□');
		ps->foodscore = 10;
	}
	else if((x >= 10 && x < 46) && ((y >= 5 && y <= 8) || (y >= 18 && y <= 21)))
	{
		wprintf(L"%lc", L'●');
		ps->foodscore = 8;
	}
	else if (((x >= 10 && x <= 16) || (x >= 40 && x <= 46)) && (y >= 9 && y <= 17))
	{
		wprintf(L"%lc", L'●');
		ps->foodscore = 8;
	}
	else
	{
		ps->foodscore =6;
		wprintf(L"%lc", L'★');
	}
}                          

//开始
void gamestart(psnack ps)
{
	//控制台大小，名字的设计
	system("mode con cols=100 lines=30");
	system("title Greedy Snake");
	//隐藏光标
	disdisplayInfo();
	//打印说明界面
	printexplanation();
	creatmap();
	//蛇身初始化
	snackinit(ps);
	//创建食物
	creatfood(ps);
	SetPos(17, 12);
	system("pause");
	SetPos(17, 12);
	wprintf(L"%ls",L"                          ");
}
//游戏暂停
void pause()
{
	while (1)
	{
		Sleep(300);
		if (GET_KEYVALUE(VK_SPACE))
		{
			break;
		}
	}
}
void eatfood(psnack ps, psnacknode pnext)
{
	//可以进行头插一个新节点或将食物的节点头插，然后再尾节点打印两个空格然后，在尾删，打印
	//插入新节点
	psnacknode pcur = ps->phead;
	pnext->next = ps->phead;
	ps->phead = pnext;	
	//加分
	ps->score += ps->foodscore;
	//释放食物
	free(ps->pfood);
	ps->pfood = NULL;
	//创建食物
	creatfood(ps);
	//打印蛇身
	printsnack(ps->phead);
}
//下一步没有吃到食物
void nofood(psnack ps, psnacknode pnext)
{
	//头插
	pnext->next = ps->phead;
	ps->phead = pnext;
	//找到倒数第二个节点的地址
	psnacknode pcur = ps->phead;
	while (pcur->next->next)//找到倒数第二个节点
	{
		SetPos(pcur->x, pcur->y);
		wprintf(L"%lc", L'●');
		pcur = pcur->next;
	}
	psnacknode ptail = pcur->next;//尾节点
	pcur->next = NULL;//尾删
	SetPos(ptail->x, ptail->y);
	wprintf(L"%ls", L"  ");
	free(ptail);
}
/*
* @brief 蛇身的行走 吃到食物加节点，没吃到正常走 都会头插一个新节点
* @param snack型结构体
*/
void snackmove(psnack ps)
{
	int x = 0;
	int y = 0;
	if (ps->direction == UP)
	{
		x = ps->phead->x;
		y = ps->phead->y - 1;
	}
	else if (ps->direction == DOWN)
	{
		x = ps->phead->x;
		y = ps->phead->y + 1;
	}
	else if (ps->direction == LEFT)
	{
		x = ps->phead->x-2;
		y = ps->phead->y;
	}
	else if (ps->direction == RIGHT)
	{
		x = ps->phead->x+2;
		y = ps->phead->y;
	}
	psnacknode nextnode = creatsnacknode(x, y);
	//下一步吃到食物
	if (nextnode->x == ps->pfood->x && nextnode->y == ps->pfood->y)
	{
		eatfood(ps, nextnode);
	}
	else
	{
		//下一步没有吃到食物
		nofood(ps, nextnode);
	}
}

void judgekillbywall(psnack ps)
{
	psnacknode pcur = ps->phead;

	if (pcur->x == 0 || pcur->x == 56 || pcur->y == 0 || pcur->y == 26)
	{
		SetPos(15, 19);
		wprintf(L"%ls", L"你撞墙了");
		ps->gamestatus = KILL_BY_WALL;
	}
}
void judgekillbyself(psnack ps)
{
	psnacknode pcur = ps->phead->next;
	while (pcur)
	{
		if ((ps->phead->x == pcur->x) && (ps->phead->y == pcur->y))
		{
			SetPos(15, 19);
			wprintf(L"%ls", L"你吃到你自己了");
			ps->gamestatus = KILL_BY_SELF;
			break;
		}
		pcur = pcur->next;
	}
}
	//要改变的因变量放在自变量的地方
	//游戏运行}
void gamerun(psnack ps)
{
	do
	{
		SetPos(62, 14);
		wprintf(L"得分：%d分 每个食物得分：%2d分", ps->score, ps->foodscore);
		if (GET_KEYVALUE(VK_UP)&&ps->direction!=DOWN)
		{
			ps->direction = UP;
		}
		else if (GET_KEYVALUE(VK_DOWN) && ps->direction != UP)
		{
			ps->direction = DOWN;
		}
		else if(GET_KEYVALUE(VK_LEFT) && ps->direction != RIGHT)
		{
			ps->direction = LEFT;
		}
		else if (GET_KEYVALUE(VK_RIGHT) && ps->direction != LEFT)
		{
			ps->direction = RIGHT;
		}
		else if (GET_KEYVALUE(VK_SPACE))
		{
			//空格暂停
			pause();
		}
		else if (GET_KEYVALUE(VK_F3))
		{
			//加速
			if (ps->sleeptime > 90) //250 160 
			{
				ps->sleeptime -= 40;
				ps->foodscore += 1;
			}
		}
		else if (GET_KEYVALUE(VK_F4))
		{
			//减速 6 - 10 - 14
			if (ps->foodscore > 6)
			{
				ps->sleeptime += 40;
				ps->foodscore -= 1;
			}
		}
		else if (GET_KEYVALUE(VK_ESCAPE))
		{
			//退出
			ps->gamestatus = EXIT_NORMAL;
		}
		Sleep(ps->sleeptime);//睡眠一下
		//走一步
		 snackmove(ps);
		 //判断是否撞墙或者要到自己
		 judgekillbywall(ps);
		 judgekillbyself(ps);
	} while (ps->gamestatus == NORMAL);
}

//游戏结束
void gameover(psnack ps)
{
	if (ps->gamestatus == EXIT_NORMAL)
	{
		SetPos(15, 19);
		wprintf(L"%ls", L"已退出游戏");
	}
	//释放节点
	psnacknode pcur =ps->phead;
	while (pcur)
	{
		psnacknode pnext = pcur->next;
		free(pcur);
		pcur = pnext;
	}
	free(ps->pfood);
	SetPos(0, 27);
}
