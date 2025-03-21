#pragma once
#define _CRT_SECURE_NO_WARNINGS

/***********************************************
功能：游戏逻辑实现的相关宏定义
编写者：韩贤煜
版本：v3
日期：2025.03.16
***********************************************/

#define X0 300 // 游戏背景起始的x坐标
#define Y0 200 // 游戏背景起始的y坐标
#define XNUM 30 // x轴上背景方格的数量
#define YNUM 25 // y轴上背景方格的数量
#define WIDTH 20 // 每个方格的宽度
#define HEIGHT 20 // 每个方格的高度
#define DIRNUM 4 // 蛇的移动方向的个数
#define UP 1 // 蛇的移动方向上
#define DOWN 2 // 蛇的移动方向下
#define LEFT 3 // 蛇的移动方向左
#define RIGHT 4 // 蛇的移动方向右
#define INITSPEED 700 // 蛇的初始移动速度(准确讲是计时器的时间)
#define SPEEDINCREASE 100 // 设定加一次速所需要的分数
#define SCOREINCREASE 10 // 设定吃一次食物所加的分数

#define edgeColor RGB(0, 0, 0) // 边缘颜色
#define backGroundColor RGB(255, 255, 255) // 背景颜色
#define foodColor RGB(255, 0, 0) // 食物颜色
#define snakeHeadColor RGB(30, 144, 255) // 蛇头颜色
#define snakeBodyColor RGB(173, 255, 47) // 蛇身颜色

#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

/***********************************************
功能：方格的定义, 包含x和y两个坐标
编写者：韩贤煜
版本：v1
日期：2025.03.16
***********************************************/
struct block
{
	int x;
	int y;
};

/***********************************************
功能：双链表结点的定义, 用于创建蛇 
编写者：韩贤煜
版本：v1
日期：2025.03.16
***********************************************/
struct node
{
	block val;
	node* pre;
	node* next;
};

/***********************************************
功能：游戏逻辑实现的相关全局变量
编写者：韩贤煜
版本：v1
日期：2025.03.16
***********************************************/

block food; // 食物方格

node* head; // 蛇的头指针
node* tail; // 蛇的尾指针

int speed; // 蛇的移动速度
int dir; // 蛇的移动方向
int score; // 游戏得分
int level;  // 游戏等级
int maxscore; // 游戏最高得分
int gameover; // 游戏结束标志
int startFlag; // 游戏开始标志
int pauseFlag; // 游戏暂停标志
WCHAR s[200]; // MessageBox输出的字符串

/***********************************************
功能：头文件中所有函数的原型声明, 且顺序与函数定义的顺序一致
编写者：韩贤煜
版本：v3
日期：2025.03.16
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
功能: 写入在游戏结束时弹出的MessageBox中显示的分数, 等级, 历史最高分, 以及死亡方式
形参：void
返回值：void
编写者：韩贤煜
版本：v2
日期：2025.03.16
***********************************************/

/***********************************************
功能: 撞墙信息的写入
形参：void
返回值：void
编写者：韩贤煜
版本：v2
日期：2025.03.16
***********************************************/
void setPrompt_01()
{
	wsprintf(s, L"你撞到墙了, 游戏结束\n分数: %d\n等级 : %d\n历史最高分: %d", score, level, maxscore);
}

/***********************************************
功能: 咬到自己的信息的写入
形参：void
返回值：void
编写者：韩贤煜
版本：v2
日期：2025.03.16
***********************************************/
void setPrompt_02()
{
	wsprintf(s, L"你咬到自己了, 游戏结束\n分数: %d\n等级: %d\n历史最高分: %d", score, level, maxscore);
}

/***********************************************
功能: 手动结束游戏的信息的写入
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.16
***********************************************/
void setPrompt_03()
{
	wsprintf(s, L"你手动结束了游戏\n分数: %d\n等级: %d\n历史最高分: %d", score, level, maxscore);
}

/***********************************************
功能：在不同按钮点击后以及游戏结束后, 改变相应的按钮的状态
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.16
***********************************************/

/***********************************************
功能：游戏初始化时, 改变相应按钮的状态
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.16
***********************************************/
void initButtonShift()
{
	EnableWindow(hWndStart, TRUE);
	EnableWindow(hWndPause, FALSE);
	EnableWindow(hWndEnd, FALSE);
	EnableWindow(hWndRestart, FALSE);
}

/***********************************************
功能：点击开始按钮后或者敲击空格键后, 改变相应的按钮的状态
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.16
***********************************************/
void startButtonShift()
{
	EnableWindow(hWndStart, FALSE);
	EnableWindow(hWndPause, TRUE);
	EnableWindow(hWndEnd, TRUE);
	EnableWindow(hWndRestart, FALSE);
}

/***********************************************
功能：点击暂停按钮后或者敲击ESC键后, 改变相应的按钮的状态
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.16
***********************************************/
void pauseButtonShift()
{
	EnableWindow(hWndStart, FALSE);
	EnableWindow(hWndPause, TRUE);
	EnableWindow(hWndEnd, TRUE);
	EnableWindow(hWndRestart, TRUE);
}

/***********************************************
功能：点击继续按钮后或者敲击空格键后, 改变相应的按钮的状态
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.16
***********************************************/
void continueButtonShift()
{
	EnableWindow(hWndStart, FALSE);
	EnableWindow(hWndPause, TRUE);
	EnableWindow(hWndEnd, TRUE);
	EnableWindow(hWndRestart, FALSE);
}

/***********************************************
功能：点击结束按钮后, 改变相应的按钮的状态
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.16
***********************************************/
void endButtonShift()
{
	EnableWindow(hWndStart, FALSE);
	EnableWindow(hWndPause, FALSE);
	EnableWindow(hWndEnd, FALSE);
	EnableWindow(hWndRestart, TRUE);
}

/***********************************************
功能：游戏结束后, 改变相应的按钮的状态
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.16
***********************************************/
void gameoverButtonShift()
{
	EnableWindow(hWndStart, FALSE);
	EnableWindow(hWndPause, FALSE);
	EnableWindow(hWndEnd, FALSE);
	EnableWindow(hWndRestart, TRUE);
}

/***********************************************
功能：双链表的操作集, 包括 头结点的插入 和 尾结点的删除
形参：block b 或者 void
返回值：void
编写者：韩贤煜
版本：v1
日期：2025.03.16
***********************************************/

/***********************************************
功能：头结点的插入
形参：block b
返回值：void
编写者：韩贤煜
版本：v1
日期：2025.03.16
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
功能：尾结点的删除/尾结点前移
形参： void
返回值：void
编写者：韩贤煜
版本：v1
日期：2025.03.16
***********************************************/
void tailNodeMove()
{
	tail = tail->pre;
	tail->next = NULL;
}

/***********************************************
功能：画图类, 画出背景, 蛇, 食物
形参：block b 或者 void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.16
***********************************************/

/***********************************************
功能：绘制边界
形参：block b
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.16
***********************************************/
void drawEdge(block b) 
{
	drawRectangle(b.x, b.y, b.x + WIDTH, b.y + HEIGHT, edgeColor);
}

/***********************************************
功能：绘制背景
形参：block b
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.16
***********************************************/
void drawBackGround(block b)
{
	drawRectangle(b.x, b.y, b.x + WIDTH, b.y + HEIGHT, backGroundColor);
}

/***********************************************
功能：绘制蛇头
形参：block b
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.16
***********************************************/
void drawSnakeHead(block b)
{
	drawRectangle(b.x, b.y, b.x + WIDTH, b.y + HEIGHT, snakeHeadColor);
}

/***********************************************
功能：绘制蛇身
形参：block b
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.16
***********************************************/
void drawSnakeBody(block b)
{
	drawRectangle(b.x, b.y, b.x + WIDTH, b.y + HEIGHT, snakeBodyColor);
}

/***********************************************
功能：食物类, 包括 绘制食物, 随机食物的坐标, 判定食物是否在蛇身上, 初始化食物
形参：void
返回值：void 或 int
编写者：韩贤煜
版本：v2
日期：2025.03.16
***********************************************/

/***********************************************
功能：绘制食物
形参：void
返回值：void
编写者：韩贤煜
版本：v2
日期：2025.03.16
***********************************************/
void drawFood()
{
	block b;

	b.x = X0 + food.x * WIDTH;
	b.y = Y0 + food.y * HEIGHT;
	drawRectangle(b.x, b.y, b.x + WIDTH, b.y + HEIGHT, foodColor);
}

/***********************************************
功能：随机食物的坐标
形参：void
返回值：void
编写者：韩贤煜
版本：v2
日期：2025.03.16
***********************************************/
void randFood()
{
	srand((unsigned int)time(NULL));
	food.x = rand() % XNUM + 1;
	food.y = rand() % YNUM + 1;
}

/***********************************************
功能：判定食物是否在蛇身上
形参：void
返回值：int
编写者：韩贤煜
版本：v2
日期：2025.03.16
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
功能：初始化类, 包括 初始化背景, 初始化食物, 初始化蛇
形参：void
返回值：void
编写者：韩贤煜
版本：v2
日期：2025.03.16
***********************************************/

/***********************************************
功能：初始化背景
形参：void
返回值：void
编写者：韩贤煜
版本：v2
日期：2025.03.16
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
功能：初始化食物
形参：void
返回值：void
编写者：韩贤煜
版本：v2
日期：2025.03.16
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
功能：蛇类, 包括 蛇移动方向的初始化, 初始化蛇, 绘制蛇, 蛇的四向移动, 蛇的速度改变, 蛇的碰撞判定, 蛇吃食物的判定, 销毁蛇
形参：void
返回值：void 或 int
编写者：韩贤煜
版本：v3
日期：2025.03.16
***********************************************/

/***********************************************
功能：蛇移动方向的初始化
形参：void
返回值：void
编写者：韩贤煜
版本：v2
日期：2025.03.21
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
功能：初始化蛇
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.16
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
功能：绘制蛇
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.16
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
功能：让蛇朝移动方向移动
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.16
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
		MessageBox(hWnd, s, L"游戏结束", 0);

		return;
	}
	else if (crashBody())
	{
		gameoverSet();
		setPrompt_02();
		MessageBox(hWnd, s, L"游戏结束", 0);

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
功能：蛇往上移动
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.16
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
功能：蛇往下移动
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.16
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
功能：蛇往左移动
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.16
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
功能：蛇往右移动
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.16
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
功能：改变蛇的移动速度
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.16
***********************************************/
void speedChange()
{
	speed = INITSPEED - level * 100;
	stopMove();
	setMovespeed(speed);
}

/***********************************************
功能：蛇的边界碰撞判定
形参：void
返回值：int
编写者：韩贤煜
版本：v3
日期：2025.03.16
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
功能：蛇的身体碰撞判定
形参：void
返回值：int
编写者：韩贤煜
版本：v3
日期：2025.03.16
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
功能：蛇吃食物的判定
形参：void
返回值：int
编写者：韩贤煜
版本：v3
日期：2025.03.16
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
功能：销毁蛇
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.16
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
功能：游戏结束后进行相应的设置
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.17
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
功能：初始化程序
形参：void
返回值：void
编写者: 韩贤煜
版本：v3
日期：2025.03.16
***********************************************/
void initGame()
{
	//AllocConsole();
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	//以下位置添加代码
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
功能：开始 按钮执行该函数
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.17
***********************************************/
void btnBeginClick()
{
	startButtonShift();
	setMovespeed(speed);
	startFlag = 1;
	pauseFlag = 0;
}

/***********************************************
功能：暂停、继续 按钮执行该函数
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.17
***********************************************/
void btnPauseClick()
{
	if (pauseFlag == 0)
	{
		pauseFlag = 1;
		SetWindowText(hWndPause, szContinue);
		pauseButtonShift();
		MessageBox(hWnd, L"按继续按钮 或 敲击空格键 继续游戏", L"提示", 0);
	}
	else
	{
		pauseFlag = 0;
		SetWindowText(hWndPause, szPause);
		continueButtonShift();
	}
}

/***********************************************
功能：结束 按钮执行该函数
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.17
***********************************************/
void btnEndClick()
{
	//MessageBox(hWnd, L"程序结束", L"提示", 0);

	//以下位置添加代码
	gameoverSet();
	setPrompt_03();
	SetWindowText(hWndPause, szPause);
	endButtonShift();
	MessageBox(hWnd, s, L"游戏结束", 0);
}

/***********************************************
功能：再次开始 按钮执行该函数
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.17
***********************************************/
void btnRestartClick()
{
	initGame();
	SetWindowText(hWndPause, szPause);
	btnBeginClick();
}

/***********************************************
功能：暂停 敲击ESC执行该函数
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.17
***********************************************/
void btnEscPress()
{
	if (pauseFlag == 0)
	{
		pauseFlag = 1;
		SetWindowText(hWndPause, szContinue);
		pauseButtonShift();
		MessageBox(hWnd, L"按继续按钮 或 敲击空格键 继续游戏", L"提示", 0);
	}
}

/***********************************************
功能：开始, 继续 敲击空格键执行该函数
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.17
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
功能：设定定时器指向的动作/函数
形参：void
返回值：void
编写者：韩贤煜
版本：v3
日期：2025.03.17
***********************************************/
void timer_01()
{
	if (pauseFlag == 0 && gameover == 0)
	{
		snakeMove();
	}
}

#pragma once
