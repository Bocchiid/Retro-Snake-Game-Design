/**********************************************
项目名称：贪吃蛇游戏设计
功能：见示例
提示：不要修改本文件中的所有内容，自己编写的程序写到 myfile.h 文件中

//创建窗口函数
hWndStart = CreateWindowW(L"button", szBegin,
            BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
            x, y, width, hight,
            hWnd, (HMENU)HWNDSTART,
            ((LPCREATESTRUCT)lParam)->hInstance, NULL);
//设置窗口不能被按下
EnableWindow(hWndPause, FALSE);
//设置窗口的文本
SetWindowText(hWndLable, s);
//设置窗口的位置
SetWindowPos(hWndPause, NULL, 10, 10, 100, 100, SWP_NOSIZE);
//调用DOS界面
AllocConsole(); 
***********************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>

#define MAX_LOADSTRING 100
#define HWNDSTART (WM_USER+1)
#define HWNDPAUSE (WM_USER + 2)
#define HWNDLABLE (WM_USER+3)
#define HWNDEND (WM_USER+4)
#define HWNDRESTART (WM_USER+5)
#define HWNTITLELABLE (WM_USER+6)
#define TIMER1 (WM_USER + 100)

//定义控件
HWND hWndStart;
HWND hWndPause;
HWND hWndLable;
HWND hWndTitleLable;
HWND hWndEnd;
HWND hWndRestart;
HWND hWndLableCopyright;

//控件标题
WCHAR szBegin[MAX_LOADSTRING] = L"开始";
WCHAR szEnd[MAX_LOADSTRING] = L"结束";
WCHAR szPause[MAX_LOADSTRING] = L"暂停";
WCHAR szContinue[MAX_LOADSTRING] = L"继续";
WCHAR szRestart[MAX_LOADSTRING] = L"重新开始";
WCHAR szCopyright[MAX_LOADSTRING] = L"Copyright:\n作者: 韩贤煜 \n日期：2025.03.16";

// 全局变量:
HINSTANCE hInst;                    // 当前实例
HWND hWnd;                         //主窗体

HANDLE hStdout;
WCHAR szTitle[MAX_LOADSTRING] = L"SNAKEMOVE";                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING] = L"mainclass";            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

/***********************************************
功能：创建计时器，每间隔n 毫秒发送 WM_TIMER 消息
形参：整数，单位毫秒
返回值：void
编写者：
版本：V1
日期：2025.02.01
***********************************************/
void setMovespeed(int n)
{
    SetTimer(hWnd, TIMER1, n, NULL);
}

/***********************************************
功能：销毁计时器
形参：
返回值：void
编写者：
版本：V1
日期：2025.02.01
***********************************************/
void stopMove()
{
    KillTimer(hWnd, TIMER1);
}
/***********************************************
功能：画矩形
形参：x1、y1为起点坐标，x2、y2为矩形的对角坐标，
      color为整数，表示颜色，可以其他应用程序（如WORD），找到用整型表示的颜色
返回值：void
编写者：
版本：V1
日期：2025.02.01
***********************************************/
void drawRectangle(int x1, int y1, int x2, int y2, int color)
{
    HDC hdc;
    hdc = GetDC(hWnd);
    HBRUSH hBrush;
    RECT rect;
    POINT a[5];
    a[0].x = x1, a[0].y = y1;
    a[1].x = x2, a[1].y = y1;
    a[2].x = x2, a[2].y = y2;
    a[3].x = x1, a[3].y = y2;
    a[4].x = x1, a[4].y = y1;
    SetRect(&rect, x1, y1, x2, y2);

    hBrush = CreateSolidBrush(color);
    FillRect(hdc, &rect, hBrush);      //填充矩形
    SelectObject(hdc, GetStockObject(BLACK_PEN));
    Polyline(hdc, a, 5);               //画边框

    ReleaseDC(hWnd, hdc);
    DeleteObject(hBrush);
}
/***********************************************
功能：显示等级分数及提示信息
形参：二个整型变时 ，分别表示等级和分数。
返回值：void
编写者：
版本：V1
日期：2025.02.01
***********************************************/
void printPrompt(int level, int score)
{
    WCHAR s[200];
    wsprintf(s, L"    等级:%d\n    分数:%d", level, score);
    SetWindowText(hWndLable, s);
}
/***********************************************
* 功能：在DOS窗口中输出整数
形参：整型变量。
返回值：void
编写者：
版本：V1
日期：2025.02.01
***********************************************/
void printNum(int x)
{
    char txt[100];
    sprintf_s(txt, "%d\n", x);
    WriteConsoleA(hStdout, txt, strlen(txt), NULL, NULL);
}
/***********************************************
* 功能：在DOS窗口中输出字符串
形参：字符串。
返回值：void
编写者：
版本：V1
日期：2025.02.01
***********************************************/
void printString(const char s[])
{
    char txt[100];
    sprintf_s(txt, "%s\n", s);
    WriteConsoleA(hStdout, txt, strlen(txt), NULL, NULL);
}
/***********************************************
功能：指定位置输出字符串
形参：整数x，y为屏幕坐标， S需要显示的字符串
返回值：void
版本：V1
日期：2025.02.01
***********************************************/
void printText(int x, int y, const char* s)
{
    HDC hdc;
    hdc = GetDC(hWnd);
    TextOutA(hdc, x, y, s, strlen(s));
    ReleaseDC(hWnd, hdc);
}
/***********************************************
功能：指定位置输出字符串
形参：整数x，y为屏幕坐标， a为整数
返回值：void
版本：V1
日期：2025.02.01
***********************************************/
void printNum(int x, int y, int a)
{
    char str[100];
    sprintf(str, "%5d", a);
    printText(x, y, str);
}

/**************************************** 
//自己编写的程序全部写在 myfile.h头文件中
*****************************************/

#include "myfile.h"

//VC++应用程序入口
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    //UNREFERENCED_PARAMETER(hPrevInstance);
    //UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    //LoadStringW(hInstance, IDC_PROJECT4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    //HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT4));
	
	//调用初始化函数 
    initGame();

    //AllocConsole();
    //hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, NULL, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}


//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex = { 0 };

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    //wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT4));
    //wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    //wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJECT4);
    wcex.lpszClassName = szWindowClass;
    //wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 将实例句柄存储在全局变量中

    hWnd = CreateWindowW(szWindowClass, szTitle, WS_CAPTION | WS_SYSMENU,
        100, 100, 1100, 900, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    
    case WM_TIMER:    
        //添加定时器消息处理函数
        timer_01();
        break;

    case  WM_KEYDOWN:        //键盘消息处理程序
    {
        switch ((int)wParam)
        {
        case VK_UP:        
            //添加向上　↑键处理程序
            moveUp();
            break;

        case VK_DOWN:      
            // 添加向下　↓键处理程序
            moveDown();
            break;

        case VK_LEFT:      
            //添加向左　←键处理程序
            moveLeft();
            break;

        case VK_RIGHT:     
            // 添加向右　→键处理程序
            moveRight();
            break;

        case VK_RETURN:    
            //添加回车  键处理程序
            btnBeginClick();
            break;

        case VK_ESCAPE:    
            //添加Esc键　处理程序. 暂停　
            btnEscPress();
            break;

        case VK_SPACE:     
            //添加空格键  键处理程序， 继续
            btnSpacePress();
            break;
        }
    }
    break;
    
    
    case WM_CREATE:  //窗体创建消息，在主窗体上布置四个按钮和一个显示按钮
    {               

        int hight = 30;
        int width = 120;
        int x = 100;
        int y = 250;

        HFONT hFont = CreateFont(
            16, // 字体高度
            0, // 字体宽度
            0, // 旋转角度
            0, // 倾斜角度
            FW_NORMAL, // 字重
            FALSE, // 是否有斜体
            FALSE, // 是否有下划线
            FALSE, // 是否有删除线
            GB2312_CHARSET, // 字符集
            OUT_DEFAULT_PRECIS, // 输出精度
            CLIP_DEFAULT_PRECIS, // 裁剪精度
            DEFAULT_QUALITY, // 字体质量
            DEFAULT_PITCH | FF_DONTCARE, // 字体间距和家族
            TEXT("宋体") // 字体名称
        );

        //开始按钮
        hWndStart = CreateWindowW(L"button", szBegin,
            BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
            x, y, width, hight,
            hWnd, (HMENU)HWNDSTART,
            ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        //暂停按钮
        hWndPause = CreateWindowW(L"button", szPause,
            BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, // | WS_DISABLED,
            x, y + 50, width, hight,
            hWnd, (HMENU)HWNDPAUSE,
            ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        //结束按钮
        hWndEnd = CreateWindowW(L"button", szEnd,
            BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, // | WS_DISABLED,
            x, y + 100, width, hight,
            hWnd, (HMENU)HWNDEND,
            ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        //重新开始按钮
        hWndRestart = CreateWindowW(L"button", szRestart,
            BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, //  | WS_DISABLED,
            x, y + 150, width, hight,
            hWnd, (HMENU)HWNDRESTART,
            ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        //显示按钮
        hWndLable = CreateWindowW(L"static", L"    等级:1\n    分数:0",
            SS_LEFT | WS_VISIBLE | WS_CHILD,
            x , y - 60, 120, 40,
            hWnd, (HMENU)HWNDLABLE,
            ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        hWndTitleLable = CreateWindowW(L"static", L"            应用程序设计: 贪吃蛇\n          按开始键或空格健开始游戏\n   Copyright:作者: 韩贤煜  日期：2025.03.16",
            SS_LEFT | WS_VISIBLE | WS_CHILD,
            x + 250, y - 150 , 360, 60,
            hWnd, (HMENU)HWNTITLELABLE,
            ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        hWndLableCopyright = CreateWindowW(L"static", szCopyright,
            SS_LEFT | WS_CHILD,
            x, y + 320, 120, 100,
            hWnd, (HMENU)HWNDLABLE,
            ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        SendMessage(hWndStart, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hWndPause, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hWndRestart, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hWndEnd, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hWndLable, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hWndTitleLable, WM_SETFONT, (WPARAM)hFont, TRUE);
        SendMessage(hWndLableCopyright, WM_SETFONT, (WPARAM)hFont, TRUE);        
                 
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 分析按钮和菜单:
        switch (wmId)
        {
        case HWNDSTART:   //开始按钮功能
            btnBeginClick();
            break;

        case HWNDPAUSE:
            btnPauseClick();    //暂停按钮 
            break;

        case HWNDEND:              //结束按钮
            btnEndClick();
            break;

        case HWNDRESTART:        //再次开始按钮
            btnRestartClick();
            break;
        }
        SetFocus(hWnd);
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 在此处添加使用 hdc 的任何绘图代码...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
