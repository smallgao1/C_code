#pragma once
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#define WALL L'��'
#define POS_X 24
#define POS_y 5
#define BODY L'��'


#define GET_KEYVALUE(x) ((GetAsyncKeyState(x)&0x01)?1:0)
//̰��������һ��һ���Ľڵ����
typedef struct snacknode
{
	int x;
	int y;
	struct snacknode* next;//��һ���ߵĽڵ�
}snacknode;

typedef snacknode* psnacknode;

//̰���߷���
enum DIR  
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

//̰����״̬
enum gamestatus
{
	NORMAL,
	KILL_BY_WALL,
	KILL_BY_SELF,
	EXIT_NORMAL
};
typedef struct snack
{
	psnacknode phead;//̰���ߵ�ͷ��ָ��
	psnacknode pfood;//ʳ���ָ��
	enum DIR direction;
	enum gamestatus gamestatus;
	int score;//��ǰ��õķ���
	int foodscore;//ÿ��ʳ��ķ���
	int sleeptime;
}Snack, * psnack;
//̰����ͨ����ʱ��������ʾ�ٶ�

//���ù��λ��
void SetPos(short x, short y);

//ͷ������ڵ�
void pushsnacknodefront(psnacknode* pphead, int x, int y);

//����ʳ��
void creatfood(psnack ps);

//��ӡ����
void printsnack(psnacknode phead);

//̰���ߵ�ͼ
void gamestart(psnack ps);

//������
void snackmove(psnack ps);

//��һ���Ե�ʳ��
void eatfood(psnack ps,psnacknode pnext);

//��һ��û�гԵ�ʳ��
void nofood(psnack ps, psnacknode pnext);

//��Ϸ����
void gamerun(psnack ps);

//�ж��Ƿ�ײǽ����Ҫ���Լ�
void judgekillbywall(psnack ps);

void judgekillbyself(psnack ps);

//��Ϸ��������
void gameover(psnack ps);

