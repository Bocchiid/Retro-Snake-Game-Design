/**********************************************
��Ŀ���ƣ�̰������Ϸ���
���ܣ���ʾ��
��ʾ����Ҫ�޸ı��ļ��е��������ݣ��Լ���д�ĳ���д�� myfile.h �ļ���

//�������ں���
hWndStart = CreateWindowW(L"button", szBegin,
            BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
            x, y, width, hight,
            hWnd, (HMENU)HWNDSTART,
            ((LPCREATESTRUCT)lParam)->hInstance, NULL);
//���ô��ڲ��ܱ�����
EnableWindow(hWndPause, FALSE);
//���ô��ڵ��ı�
SetWindowText(hWndLable, s);
//���ô��ڵ�λ��
SetWindowPos(hWndPause, NULL, 10, 10, 100, 100, SWP_NOSIZE);
//����DOS����
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

//����ؼ�
HWND hWndStart;
HWND hWndPause;
HWND hWndLable;
HWND hWndTitleLable;
HWND hWndEnd;
HWND hWndRestart;
HWND hWndLableCopyright;

//�ؼ�����
WCHAR szBegin[MAX_LOADSTRING] = L"��ʼ";
WCHAR szEnd[MAX_LOADSTRING] = L"����";
WCHAR szPause[MAX_LOADSTRING] = L"��ͣ";
WCHAR szContinue[MAX_LOADSTRING] = L"����";
WCHAR szRestart[MAX_LOADSTRING] = L"���¿�ʼ";
WCHAR szCopyright[MAX_LOADSTRING] = L"Copyright:\n����: ������ \n���ڣ�2025.03.16";

// ȫ�ֱ���:
HINSTANCE hInst;                    // ��ǰʵ��
HWND hWnd;                         //������

HANDLE hStdout;
WCHAR szTitle[MAX_LOADSTRING] = L"SNAKEMOVE";                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING] = L"mainclass";            // ����������

// �˴���ģ���а����ĺ�����ǰ������:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

/***********************************************
���ܣ�������ʱ����ÿ���n ���뷢�� WM_TIMER ��Ϣ
�βΣ���������λ����
����ֵ��void
��д�ߣ�
�汾��V1
���ڣ�2025.02.01
***********************************************/
void setMovespeed(int n)
{
    SetTimer(hWnd, TIMER1, n, NULL);
}

/***********************************************
���ܣ����ټ�ʱ��
�βΣ�
����ֵ��void
��д�ߣ�
�汾��V1
���ڣ�2025.02.01
***********************************************/
void stopMove()
{
    KillTimer(hWnd, TIMER1);
}
/***********************************************
���ܣ�������
�βΣ�x1��y1Ϊ������꣬x2��y2Ϊ���εĶԽ����꣬
      colorΪ��������ʾ��ɫ����������Ӧ�ó�����WORD�����ҵ������ͱ�ʾ����ɫ
����ֵ��void
��д�ߣ�
�汾��V1
���ڣ�2025.02.01
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
    FillRect(hdc, &rect, hBrush);      //������
    SelectObject(hdc, GetStockObject(BLACK_PEN));
    Polyline(hdc, a, 5);               //���߿�

    ReleaseDC(hWnd, hdc);
    DeleteObject(hBrush);
}
/***********************************************
���ܣ���ʾ�ȼ���������ʾ��Ϣ
�βΣ��������ͱ�ʱ ���ֱ��ʾ�ȼ��ͷ�����
����ֵ��void
��д�ߣ�
�汾��V1
���ڣ�2025.02.01
***********************************************/
void printPrompt(int level, int score)
{
    WCHAR s[200];
    wsprintf(s, L"    �ȼ�:%d\n    ����:%d", level, score);
    SetWindowText(hWndLable, s);
}
/***********************************************
* ���ܣ���DOS�������������
�βΣ����ͱ�����
����ֵ��void
��д�ߣ�
�汾��V1
���ڣ�2025.02.01
***********************************************/
void printNum(int x)
{
    char txt[100];
    sprintf_s(txt, "%d\n", x);
    WriteConsoleA(hStdout, txt, strlen(txt), NULL, NULL);
}
/***********************************************
* ���ܣ���DOS����������ַ���
�βΣ��ַ�����
����ֵ��void
��д�ߣ�
�汾��V1
���ڣ�2025.02.01
***********************************************/
void printString(const char s[])
{
    char txt[100];
    sprintf_s(txt, "%s\n", s);
    WriteConsoleA(hStdout, txt, strlen(txt), NULL, NULL);
}
/***********************************************
���ܣ�ָ��λ������ַ���
�βΣ�����x��yΪ��Ļ���꣬ S��Ҫ��ʾ���ַ���
����ֵ��void
�汾��V1
���ڣ�2025.02.01
***********************************************/
void printText(int x, int y, const char* s)
{
    HDC hdc;
    hdc = GetDC(hWnd);
    TextOutA(hdc, x, y, s, strlen(s));
    ReleaseDC(hWnd, hdc);
}
/***********************************************
���ܣ�ָ��λ������ַ���
�βΣ�����x��yΪ��Ļ���꣬ aΪ����
����ֵ��void
�汾��V1
���ڣ�2025.02.01
***********************************************/
void printNum(int x, int y, int a)
{
    char str[100];
    sprintf(str, "%5d", a);
    printText(x, y, str);
}

/**************************************** 
//�Լ���д�ĳ���ȫ��д�� myfile.hͷ�ļ���
*****************************************/

#include "myfile.h"

//VC++Ӧ�ó������
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    //UNREFERENCED_PARAMETER(hPrevInstance);
    //UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: �ڴ˴����ô��롣

    // ��ʼ��ȫ���ַ���
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    //LoadStringW(hInstance, IDC_PROJECT4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ִ��Ӧ�ó����ʼ��:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    //HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT4));
	
	//���ó�ʼ������ 
    initGame();

    //AllocConsole();
    //hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    MSG msg;

    // ����Ϣѭ��:
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
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
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    
    case WM_TIMER:    
        //��Ӷ�ʱ����Ϣ������
        timer_01();
        break;

    case  WM_KEYDOWN:        //������Ϣ�������
    {
        switch ((int)wParam)
        {
        case VK_UP:        
            //������ϡ������������
            moveUp();
            break;

        case VK_DOWN:      
            // ������¡������������
            moveDown();
            break;

        case VK_LEFT:      
            //������󡡡����������
            moveLeft();
            break;

        case VK_RIGHT:     
            // ������ҡ������������
            moveRight();
            break;

        case VK_RETURN:    
            //��ӻس�  ���������
            btnBeginClick();
            break;

        case VK_ESCAPE:    
            //���Esc�����������. ��ͣ��
            btnEscPress();
            break;

        case VK_SPACE:     
            //��ӿո��  ��������� ����
            btnSpacePress();
            break;
        }
    }
    break;
    
    
    case WM_CREATE:  //���崴����Ϣ�����������ϲ����ĸ���ť��һ����ʾ��ť
    {               

        int hight = 30;
        int width = 120;
        int x = 100;
        int y = 250;

        HFONT hFont = CreateFont(
            16, // ����߶�
            0, // ������
            0, // ��ת�Ƕ�
            0, // ��б�Ƕ�
            FW_NORMAL, // ����
            FALSE, // �Ƿ���б��
            FALSE, // �Ƿ����»���
            FALSE, // �Ƿ���ɾ����
            GB2312_CHARSET, // �ַ���
            OUT_DEFAULT_PRECIS, // �������
            CLIP_DEFAULT_PRECIS, // �ü�����
            DEFAULT_QUALITY, // ��������
            DEFAULT_PITCH | FF_DONTCARE, // ������ͼ���
            TEXT("����") // ��������
        );

        //��ʼ��ť
        hWndStart = CreateWindowW(L"button", szBegin,
            BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
            x, y, width, hight,
            hWnd, (HMENU)HWNDSTART,
            ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        //��ͣ��ť
        hWndPause = CreateWindowW(L"button", szPause,
            BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, // | WS_DISABLED,
            x, y + 50, width, hight,
            hWnd, (HMENU)HWNDPAUSE,
            ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        //������ť
        hWndEnd = CreateWindowW(L"button", szEnd,
            BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, // | WS_DISABLED,
            x, y + 100, width, hight,
            hWnd, (HMENU)HWNDEND,
            ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        //���¿�ʼ��ť
        hWndRestart = CreateWindowW(L"button", szRestart,
            BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, //  | WS_DISABLED,
            x, y + 150, width, hight,
            hWnd, (HMENU)HWNDRESTART,
            ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        //��ʾ��ť
        hWndLable = CreateWindowW(L"static", L"    �ȼ�:1\n    ����:0",
            SS_LEFT | WS_VISIBLE | WS_CHILD,
            x , y - 60, 120, 40,
            hWnd, (HMENU)HWNDLABLE,
            ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        hWndTitleLable = CreateWindowW(L"static", L"            Ӧ�ó������: ̰����\n          ����ʼ����ո񽡿�ʼ��Ϸ\n   Copyright:����: ������  ���ڣ�2025.03.16",
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
        // ������ť�Ͳ˵�:
        switch (wmId)
        {
        case HWNDSTART:   //��ʼ��ť����
            btnBeginClick();
            break;

        case HWNDPAUSE:
            btnPauseClick();    //��ͣ��ť 
            break;

        case HWNDEND:              //������ť
            btnEndClick();
            break;

        case HWNDRESTART:        //�ٴο�ʼ��ť
            btnRestartClick();
            break;
        }
        SetFocus(hWnd);
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
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
