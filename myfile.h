#pragma once
#define _CRT_SECURE_NO_WARNINGS

/***********************************************
���ܣ���Ϸ�߼�ʵ�ֵ���غ궨��
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/

#define X0 300 // ��Ϸ������ʼ��x����
#define Y0 200 // ��Ϸ������ʼ��y����
#define XNUM 30 // x���ϱ������������
#define YNUM 25 // y���ϱ������������
#define WIDTH 20 // ÿ������Ŀ��
#define HEIGHT 20 // ÿ������ĸ߶�
#define DIRNUM 4 // �ߵ��ƶ�����ĸ���
#define UP 1 // �ߵ��ƶ�������
#define DOWN 2 // �ߵ��ƶ�������
#define LEFT 3 // �ߵ��ƶ�������
#define RIGHT 4 // �ߵ��ƶ�������
#define INITSPEED 700 // �ߵĳ�ʼ�ƶ��ٶ�(׼ȷ���Ǽ�ʱ����ʱ��)
#define SPEEDINCREASE 100 // �趨��һ��������Ҫ�ķ���
#define SCOREINCREASE 10 // �趨��һ��ʳ�����ӵķ���

#define edgeColor RGB(0, 0, 0) // ��Ե��ɫ
#define backGroundColor RGB(255, 255, 255) // ������ɫ
#define foodColor RGB(255, 0, 0) // ʳ����ɫ
#define snakeHeadColor RGB(30, 144, 255) // ��ͷ��ɫ
#define snakeBodyColor RGB(173, 255, 47) // ������ɫ

#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

/***********************************************
���ܣ�����Ķ���, ����x��y��������
��д�ߣ�������
�汾��v1
���ڣ�2025.03.16
***********************************************/
struct block
{
	int x;
	int y;
};

/***********************************************
���ܣ�˫������Ķ���, ���ڴ����� 
��д�ߣ�������
�汾��v1
���ڣ�2025.03.16
***********************************************/
struct node
{
	block val;
	node* pre;
	node* next;
};

/***********************************************
���ܣ���Ϸ�߼�ʵ�ֵ����ȫ�ֱ���
��д�ߣ�������
�汾��v1
���ڣ�2025.03.16
***********************************************/

block food; // ʳ�﷽��

node* head; // �ߵ�ͷָ��
node* tail; // �ߵ�βָ��

int speed; // �ߵ��ƶ��ٶ�
int dir; // �ߵ��ƶ�����
int score; // ��Ϸ�÷�
int level;  // ��Ϸ�ȼ�
int maxscore; // ��Ϸ��ߵ÷�
int gameover; // ��Ϸ������־
int startFlag; // ��Ϸ��ʼ��־
int pauseFlag; // ��Ϸ��ͣ��־
WCHAR s[200]; // MessageBox������ַ���

/***********************************************
���ܣ�ͷ�ļ������к�����ԭ������, ��˳���뺯�������˳��һ��
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/

void setPrompt_01();
void setPrompt_02();
void setPrompt_03();
void initButtonShift();
void startButtonShift();
void pauseButtonShift();
void continueButtonShift();
void endButtonShift();
void gameoverButtonShift();
void headNodeInsertion(block b);
void tailNodeMove();
void drawEdge(block b);
void drawBackGround(block b);
void drawSnakeHead(block b);
void drawSnakeBody(block b);
void drawFood();
void randFood();
int isOnSnake();
void initBackGround();
void initFood();
void initDir();
void initSnake();
void drawSnake();
void snakeMove();
void moveUp();
void moveDown();
void moveLeft();
void moveRight();
void speedChange();
int crashEdge();
int crashBody();
int eatFood();
void destroySnake();
void gameoverSet();
void initGame();
void btnBeginClick();
void btnPauseClick();
void btnEndClick();
void btnRestartClick();
void btnEscPress();
void btnSpacePress();
void timer_01();

/***********************************************
����: д������Ϸ����ʱ������MessageBox����ʾ�ķ���, �ȼ�, ��ʷ��߷�, �Լ�������ʽ
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v2
���ڣ�2025.03.16
***********************************************/

/***********************************************
����: ײǽ��Ϣ��д��
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v2
���ڣ�2025.03.16
***********************************************/
void setPrompt_01()
{
	wsprintf(s, L"��ײ��ǽ��, ��Ϸ����\n����: %d\n�ȼ� : %d\n��ʷ��߷�: %d", score, level, maxscore);
}

/***********************************************
����: ҧ���Լ�����Ϣ��д��
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v2
���ڣ�2025.03.16
***********************************************/
void setPrompt_02()
{
	wsprintf(s, L"��ҧ���Լ���, ��Ϸ����\n����: %d\n�ȼ�: %d\n��ʷ��߷�: %d", score, level, maxscore);
}

/***********************************************
����: �ֶ�������Ϸ����Ϣ��д��
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
void setPrompt_03()
{
	wsprintf(s, L"���ֶ���������Ϸ\n����: %d\n�ȼ�: %d\n��ʷ��߷�: %d", score, level, maxscore);
}

/***********************************************
���ܣ��ڲ�ͬ��ť������Լ���Ϸ������, �ı���Ӧ�İ�ť��״̬
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/

/***********************************************
���ܣ���Ϸ��ʼ��ʱ, �ı���Ӧ��ť��״̬
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
void initButtonShift()
{
	EnableWindow(hWndStart, TRUE);
	EnableWindow(hWndPause, FALSE);
	EnableWindow(hWndEnd, FALSE);
	EnableWindow(hWndRestart, FALSE);
}

/***********************************************
���ܣ������ʼ��ť������û��ո����, �ı���Ӧ�İ�ť��״̬
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
void startButtonShift()
{
	EnableWindow(hWndStart, FALSE);
	EnableWindow(hWndPause, TRUE);
	EnableWindow(hWndEnd, TRUE);
	EnableWindow(hWndRestart, FALSE);
}

/***********************************************
���ܣ������ͣ��ť������û�ESC����, �ı���Ӧ�İ�ť��״̬
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
void pauseButtonShift()
{
	EnableWindow(hWndStart, FALSE);
	EnableWindow(hWndPause, TRUE);
	EnableWindow(hWndEnd, TRUE);
	EnableWindow(hWndRestart, TRUE);
}

/***********************************************
���ܣ����������ť������û��ո����, �ı���Ӧ�İ�ť��״̬
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
void continueButtonShift()
{
	EnableWindow(hWndStart, FALSE);
	EnableWindow(hWndPause, TRUE);
	EnableWindow(hWndEnd, TRUE);
	EnableWindow(hWndRestart, FALSE);
}

/***********************************************
���ܣ����������ť��, �ı���Ӧ�İ�ť��״̬
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
void endButtonShift()
{
	EnableWindow(hWndStart, FALSE);
	EnableWindow(hWndPause, FALSE);
	EnableWindow(hWndEnd, FALSE);
	EnableWindow(hWndRestart, TRUE);
}

/***********************************************
���ܣ���Ϸ������, �ı���Ӧ�İ�ť��״̬
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
void gameoverButtonShift()
{
	EnableWindow(hWndStart, FALSE);
	EnableWindow(hWndPause, FALSE);
	EnableWindow(hWndEnd, FALSE);
	EnableWindow(hWndRestart, TRUE);
}

/***********************************************
���ܣ�˫����Ĳ�����, ���� ͷ���Ĳ��� �� β����ɾ��
�βΣ�block b ���� void
����ֵ��void
��д�ߣ�������
�汾��v1
���ڣ�2025.03.16
***********************************************/

/***********************************************
���ܣ�ͷ���Ĳ���
�βΣ�block b
����ֵ��void
��д�ߣ�������
�汾��v1
���ڣ�2025.03.16
***********************************************/
void headNodeInsertion(block b) 
{
	node* s = (node*)malloc(sizeof(node) * 1);
	s->val = b;
	s->next = head->next;
	s->pre = head;
	head->next->pre = s;
	head->next = s;
}

/***********************************************
���ܣ�β����ɾ��/β���ǰ��
�βΣ� void
����ֵ��void
��д�ߣ�������
�汾��v1
���ڣ�2025.03.16
***********************************************/
void tailNodeMove()
{
	tail = tail->pre;
	tail->next = NULL;
}

/***********************************************
���ܣ���ͼ��, ��������, ��, ʳ��
�βΣ�block b ���� void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/

/***********************************************
���ܣ����Ʊ߽�
�βΣ�block b
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
void drawEdge(block b) 
{
	drawRectangle(b.x, b.y, b.x + WIDTH, b.y + HEIGHT, edgeColor);
}

/***********************************************
���ܣ����Ʊ���
�βΣ�block b
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
void drawBackGround(block b)
{
	drawRectangle(b.x, b.y, b.x + WIDTH, b.y + HEIGHT, backGroundColor);
}

/***********************************************
���ܣ�������ͷ
�βΣ�block b
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
void drawSnakeHead(block b)
{
	drawRectangle(b.x, b.y, b.x + WIDTH, b.y + HEIGHT, snakeHeadColor);
}

/***********************************************
���ܣ���������
�βΣ�block b
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
void drawSnakeBody(block b)
{
	drawRectangle(b.x, b.y, b.x + WIDTH, b.y + HEIGHT, snakeBodyColor);
}

/***********************************************
���ܣ�ʳ����, ���� ����ʳ��, ���ʳ�������, �ж�ʳ���Ƿ���������, ��ʼ��ʳ��
�βΣ�void
����ֵ��void �� int
��д�ߣ�������
�汾��v2
���ڣ�2025.03.16
***********************************************/

/***********************************************
���ܣ�����ʳ��
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v2
���ڣ�2025.03.16
***********************************************/
void drawFood()
{
	block b;

	b.x = X0 + food.x * WIDTH;
	b.y = Y0 + food.y * HEIGHT;
	drawRectangle(b.x, b.y, b.x + WIDTH, b.y + HEIGHT, foodColor);
}

/***********************************************
���ܣ����ʳ�������
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v2
���ڣ�2025.03.16
***********************************************/
void randFood()
{
	srand((unsigned int)time(NULL));
	food.x = rand() % XNUM + 1;
	food.y = rand() % YNUM + 1;
}

/***********************************************
���ܣ��ж�ʳ���Ƿ���������
�βΣ�void
����ֵ��int
��д�ߣ�������
�汾��v2
���ڣ�2025.03.16
***********************************************/
int isOnSnake()
{
	node* p = head->next;

	while (p)
	{
		if (p->val.x == food.x && p->val.y == food.y)
			return 1;

		p = p->next;
	}

	return 0;
}

/***********************************************
���ܣ���ʼ����, ���� ��ʼ������, ��ʼ��ʳ��, ��ʼ����
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v2
���ڣ�2025.03.16
***********************************************/

/***********************************************
���ܣ���ʼ������
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v2
���ڣ�2025.03.16
***********************************************/
void initBackGround()
{
	int x, y;
	block b;

	for (x = 0; x <= XNUM + 1; x++)
	{
		for (y = 0; y <= YNUM + 1; y++)
		{
			b.x = X0 + x * WIDTH;
			b.y = Y0 + y * HEIGHT;

			if (x == 0 || y == 0 || x == XNUM + 1 || y == YNUM + 1)
			{
				drawEdge(b);
			}
			else
			{
				drawBackGround(b);
			}
		}
	}
}

/***********************************************
���ܣ���ʼ��ʳ��
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v2
���ڣ�2025.03.16
***********************************************/
void initFood()
{
	do
	{
		randFood();
	} while (isOnSnake());
	
	drawFood();
}

/***********************************************
���ܣ�����, ���� ���ƶ�����ĳ�ʼ��, ��ʼ����, ������, �ߵ������ƶ�, �ߵ��ٶȸı�, �ߵ���ײ�ж�, �߳�ʳ����ж�, ������
�βΣ�void
����ֵ��void �� int
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/

/***********************************************
���ܣ����ƶ�����ĳ�ʼ��
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v2
���ڣ�2025.03.21
***********************************************/
void initDir()
{
	do
	{
		srand((unsigned int)time(NULL));
		dir = rand() % DIRNUM + 1;
	} while (dir == DOWN);
}

/***********************************************
���ܣ���ʼ����
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
void initSnake()
{
	head = (node*)malloc(sizeof(node) * 1);
	head->next = NULL;
	head->pre = NULL;
	tail = head;

	node* p = (node*)malloc(sizeof(node) * 1);
	p->val.x = XNUM / 2;
	p->val.y = YNUM / 2;
	tail->next = p;
	p->pre = tail;
	p->next = NULL;
	tail = p;

	p = (node*)malloc(sizeof(node) * 1);
	p->val.x = XNUM / 2;
	p->val.y = YNUM / 2 + 1;
	tail->next = p;
	p->pre = tail;
	p->next = NULL;
	tail = p;
}

/***********************************************
���ܣ�������
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
void drawSnake()
{
	block b;
	node* p;

	p = head->next;

	while (p)
	{
		b.x = X0 + p->val.x * WIDTH;
		b.y = Y0 + p->val.y * HEIGHT;

		if (p == head->next)
		{
			drawSnakeHead(b);
		}
		else
		{
			drawSnakeBody(b);
		}

		p = p->next;
	}
}

/***********************************************
���ܣ����߳��ƶ������ƶ�
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
void snakeMove()
{
	block b;

	if (dir == UP)
	{
		b.x = head->next->val.x;
		b.y = head->next->val.y - 1;
	}
	else if (dir == DOWN)
	{
		b.x = head->next->val.x;
		b.y = head->next->val.y + 1;
	}
	else if (dir == LEFT)
	{
		b.x = head->next->val.x - 1;
		b.y = head->next->val.y;
	}
	else if (dir == RIGHT)
	{
		b.x = head->next->val.x + 1;
		b.y = head->next->val.y;
	}

	headNodeInsertion(b);

	if (crashEdge())
	{
		gameoverSet();
		setPrompt_01();
		MessageBox(hWnd, s, L"��Ϸ����", 0);

		return;
	}
	else if (crashBody())
	{
		gameoverSet();
		setPrompt_02();
		MessageBox(hWnd, s, L"��Ϸ����", 0);

		return;
	}

	if (eatFood())
	{
		score += SCOREINCREASE;
		level = 1 + score / SPEEDINCREASE;
		printPrompt(level, score);
		initFood();
		
		if (score != 0 && score % SPEEDINCREASE == 0)
		{
			speedChange();
		}
	}
	else
	{
		b.x = X0 + tail->val.x * WIDTH;
		b.y = Y0 + tail->val.y * HEIGHT;
		tailNodeMove();
		drawBackGround(b);
	}

	drawSnake();
}

/***********************************************
���ܣ��������ƶ�
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
void moveUp()
{
	if (pauseFlag == 0 && gameover == 0 && dir != DOWN)
	{
		dir = UP;
		snakeMove();
	}
}

/***********************************************
���ܣ��������ƶ�
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
void moveDown()
{
	if (pauseFlag == 0 && gameover == 0 && dir != UP)
	{
		dir = DOWN;
		snakeMove();
	}
}

/***********************************************
���ܣ��������ƶ�
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
void moveLeft()
{
	if (pauseFlag == 0 && gameover == 0 && dir != RIGHT)
	{
		dir = LEFT;
		snakeMove();
	}
}

/***********************************************
���ܣ��������ƶ�
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
void moveRight()
{
	if (pauseFlag == 0 && gameover == 0 && dir != LEFT)
	{
		dir = RIGHT;
		snakeMove();
	}
}

/***********************************************
���ܣ��ı��ߵ��ƶ��ٶ�
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
void speedChange()
{
	speed = INITSPEED - level * 100;
	stopMove();
	setMovespeed(speed);
}

/***********************************************
���ܣ��ߵı߽���ײ�ж�
�βΣ�void
����ֵ��int
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
int crashEdge()
{
	if (head->next->val.x == 0 || head->next->val.x == XNUM + 1 ||
		head->next->val.y == 0 || head->next->val.y == YNUM + 1)
	{
		return 1;
	}

	return 0;
}

/***********************************************
���ܣ��ߵ�������ײ�ж�
�βΣ�void
����ֵ��int
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
int crashBody()
{
	node* h = head->next;
	node* p = h->next;

	while (p)
	{
		if (h->val.x == p->val.x && h->val.y == p->val.y)
		{
			return 1;
		}

		p = p->next;
	}

	return 0;
}

/***********************************************
���ܣ��߳�ʳ����ж�
�βΣ�void
����ֵ��int
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
int eatFood()
{
	if (food.x == head->next->val.x && food.y == head->next->val.y)
	{
		return 1;
	}

	return 0;
}

/***********************************************
���ܣ�������
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.16
***********************************************/
void destroySnake()
{
	node* p, * q;

	p = head;

	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
}

/***********************************************
���ܣ���Ϸ�����������Ӧ������
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.17
***********************************************/
void gameoverSet()
{
	gameover = 1;
	gameoverButtonShift();
	destroySnake();

	if (score > maxscore)
	{
		maxscore = score;
	}
}

/***********************************************
���ܣ���ʼ������
�βΣ�void
����ֵ��void
��д��: ������
�汾��v3
���ڣ�2025.03.16
***********************************************/
void initGame()
{
	//AllocConsole();
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	//����λ����Ӵ���
	initButtonShift();
	startFlag = 0;
	pauseFlag = 1;
	gameover = 0;
	speed = INITSPEED;
	initDir();
	score = 0;
	level = 1;

	printPrompt(level, score);
	initBackGround();
	initSnake();
	initFood();
	drawSnake();
}

/***********************************************
���ܣ���ʼ ��ťִ�иú���
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.17
***********************************************/
void btnBeginClick()
{
	startButtonShift();
	setMovespeed(speed);
	startFlag = 1;
	pauseFlag = 0;
}

/***********************************************
���ܣ���ͣ������ ��ťִ�иú���
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.17
***********************************************/
void btnPauseClick()
{
	if (pauseFlag == 0)
	{
		pauseFlag = 1;
		SetWindowText(hWndPause, szContinue);
		pauseButtonShift();
		MessageBox(hWnd, L"��������ť �� �û��ո�� ������Ϸ", L"��ʾ", 0);
	}
	else
	{
		pauseFlag = 0;
		SetWindowText(hWndPause, szPause);
		continueButtonShift();
	}
}

/***********************************************
���ܣ����� ��ťִ�иú���
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.17
***********************************************/
void btnEndClick()
{
	//MessageBox(hWnd, L"�������", L"��ʾ", 0);

	//����λ����Ӵ���
	gameoverSet();
	setPrompt_03();
	SetWindowText(hWndPause, szPause);
	endButtonShift();
	MessageBox(hWnd, s, L"��Ϸ����", 0);
}

/***********************************************
���ܣ��ٴο�ʼ ��ťִ�иú���
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.17
***********************************************/
void btnRestartClick()
{
	initGame();
	SetWindowText(hWndPause, szPause);
	btnBeginClick();
}

/***********************************************
���ܣ���ͣ �û�ESCִ�иú���
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.17
***********************************************/
void btnEscPress()
{
	if (pauseFlag == 0)
	{
		pauseFlag = 1;
		SetWindowText(hWndPause, szContinue);
		pauseButtonShift();
		MessageBox(hWnd, L"��������ť �� �û��ո�� ������Ϸ", L"��ʾ", 0);
	}
}

/***********************************************
���ܣ���ʼ, ���� �û��ո��ִ�иú���
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.17
***********************************************/
void btnSpacePress()
{
	if (startFlag == 0)
	{
		btnBeginClick();
	}
	else if (pauseFlag == 1)
	{
		pauseFlag = 0;
		SetWindowText(hWndPause, szPause);
		continueButtonShift();
	}
}

/***********************************************
���ܣ��趨��ʱ��ָ��Ķ���/����
�βΣ�void
����ֵ��void
��д�ߣ�������
�汾��v3
���ڣ�2025.03.17
***********************************************/
void timer_01()
{
	if (pauseFlag == 0 && gameover == 0)
	{
		snakeMove();
	}
}

#pragma once
