#pragma once
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#define WALL L'□'
#define POS_X 24
#define POS_y 5
#define BODY L'●'


#define GET_KEYVALUE(x) ((GetAsyncKeyState(x)&0x01)?1:0)
//贪吃蛇是由一个一个的节点组成
typedef struct snacknode
{
	int x;
	int y;
	struct snacknode* next;//下一个蛇的节点
}snacknode;

typedef snacknode* psnacknode;

//贪吃蛇方向
enum DIR  
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

//贪吃蛇状态
enum gamestatus
{
	NORMAL,
	KILL_BY_WALL,
	KILL_BY_SELF,
	EXIT_NORMAL
};
typedef struct snack
{
	psnacknode phead;//贪吃蛇的头部指针
	psnacknode pfood;//食物的指针
	enum DIR direction;
	enum gamestatus gamestatus;
	int score;//当前获得的分数
	int foodscore;//每个食物的分数
	int sleeptime;
}Snack, * psnack;
//贪吃蛇通过延时函数来表示速度

//设置光标位置
void SetPos(short x, short y);

//头部插入节点
void pushsnacknodefront(psnacknode* pphead, int x, int y);

//创建食物
void creatfood(psnack ps);

//打印蛇身
void printsnack(psnacknode phead);

//贪吃蛇地图
void gamestart(psnack ps);

//蛇行走
void snackmove(psnack ps);

//下一步吃到食物
void eatfood(psnack ps,psnacknode pnext);

//下一步没有吃到食物
void nofood(psnack ps, psnacknode pnext);

//游戏运行
void gamerun(psnack ps);

//判断是否撞墙或者要到自己
void judgekillbywall(psnack ps);

void judgekillbyself(psnack ps);

//游戏结束处理
void gameover(psnack ps);

