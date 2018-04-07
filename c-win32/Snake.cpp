// Snake.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "Snake.h"
#include <windowsx.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SNAKE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_SNAKE);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_SNAKE);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_SNAKE;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED|WS_SYSMENU|WS_CAPTION|WS_THICKFRAME|WS_MINIMIZEBOX,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   
   MoveWindow(hWnd,200,100,MENUWIDTH,MENUHEIGHT,true);
   ini_data(hWnd);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int n;
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{
		case WM_CREATE:
			OnCreateButtons(hWnd);
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case BTNSTAR:
				//	OnStart(hWnd);
					OnNewGame(hWnd);
					break;
				case BTNLOAD:
					MessageBox(hWnd, "��������δ���", "�Ժ��ٲ�", MB_OK|MB_ICONINFORMATION);
					break;
				case BTNQUIT:
					if(IDYES==MessageBox(hWnd, "ȷ��Ҫ�˳�̰ʳ����", "��ʾ", MB_YESNO|MB_ICONINFORMATION)){
						DestroyWindow(hWnd);
					}
					break;
				case BTNABUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
			/*	case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;*/
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_KEYDOWN:
			if(surf==InGame)
			{
				switch(wParam)
				{
					case VK_ESCAPE:
						OnEscape(hWnd);
						break;
					case VK_UP: case 87:
						if(s0.m_pos[0].y-s0.m_pos[1].y!=1){
							s0.m_direction=UPDRC;  //����
						}
						break;
					case VK_RIGHT: case 68:
						if(s0.m_pos[0].x-s0.m_pos[1].x!=-1){
							s0.m_direction=RIGHTDRC;  //����
						}
						break;
					case VK_DOWN: case 83:
						if(s0.m_pos[0].y-s0.m_pos[1].y!=-1){
							s0.m_direction=DOWNDRC;  //����
						}
						break;
					case  VK_LEFT: case 65:
						if(s0.m_pos[0].x-s0.m_pos[1].x!=1){
							s0.m_direction=LEFTDRC;  //����
						}
						break;
				}
			}
			break;
		case WM_TIMER:
			//�����ߵ�����
			for(n=s0.len-1;n>=1;n--)
			{
				s0.m_pos[n]=s0.m_pos[n-1];
			}
			//����ͷ������
			if(UPDRC==s0.m_direction)
			{
				if(s0.m_pos[0].y==0){
					s0.m_pos[0].y=row-1;
				}
				else {
					s0.m_pos[0].y=s0.m_pos[0].y-1;
				}
			}
			else if(RIGHTDRC==s0.m_direction)
			{
				s0.m_pos[0].x=(s0.m_pos[0].x+1)%col;
			}
			else if(DOWNDRC==s0.m_direction)
			{
				s0.m_pos[0].y=(s0.m_pos[0].y+1)%row;
			}
			else if(LEFTDRC==s0.m_direction)
			{
				if(s0.m_pos[0].x==0){
					s0.m_pos[0].x=col-1;
				}
				else {
					s0.m_pos[0].x=s0.m_pos[0].x-1;
				}
			}
			//�Ե�ʳ��ʱ
			if(s0.m_pos[0].x==m_food.x&&s0.m_pos[0].y==m_food.y)
			{
				s0.len++;
				generateFood();
			}
			if(isSnakeB(s0.m_pos[0]) || isBrick(s0.m_pos[0]))
			{
				char scorstr[60]={0};
				KillTimer(hWnd,1);
				int record=ini_record();
				sprintf(scorstr,"Game over!�������յ÷�Ϊ:%3d.����ͼ��ǰ��߼�¼Ϊ:%3d.",s0.len-1,record);
				if(IDYES==MessageBox(hWnd,scorstr,"�������¿�ʼ��?",MB_YESNO|MB_ICONASTERISK))
				{
					LoadMap(mapID);
					OnStart(hWnd);
				}
				else
				{
				//	PostQuitMessage(0);
					backMenu(hWnd);
					break;
				}
			}
			hdc=GetDC(hWnd);
			InvalidateRect(hWnd,NULL,FALSE);
		//	MyPaint(hdc);
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			if(surf==InMenu){
				RECT rt;
				GetClientRect(hWnd, &rt);
				DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
			}
			else if(surf==InGame){
				MyPaint(hdc);
			}
			EndPaint(hWnd, &ps);
			break;
		case WM_SIZE:
			switch(wParam){
				case SIZE_RESTORED: //���ִ��ڴ�С
					{
						RECT crc,wrc;
						GetClientRect(hWnd,&crc);
						GetWindowRect(hWnd,&wrc);
						int borderwidth=(wrc.right-wrc.left)-(crc.right-crc.left);
						int borderheight=(wrc.bottom-wrc.top)-(crc.bottom-crc.top);
						if(surf==InMenu){
							MoveWindow(hWnd,wrc.left,wrc.top,MENUWIDTH,MENUHEIGHT,true);
						}
						else if(surf==InGame){
							MoveWindow(hWnd,wrc.left,wrc.top,col*WIDTH+borderwidth,row*HEIGHT+borderheight,true);
						}
						break;
					}
			}
			break;
		case WM_CLOSE:
			if(surf==InGame){
				KillTimer(hWnd,1);
			}
			if(IDYES==MessageBox(hWnd, "ȷ��Ҫ�˳�̰ʳ����", "��ʾ", MB_YESNO|MB_ICONINFORMATION)){
				DestroyWindow(hWnd);
			}
			else if(surf==InGame){
				SetTimer(hWnd,1,speed,NULL);
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

//������ť
void OnCreateButtons(HWND hWnd)
{	 
	hBtnStart=CreateWindow(TEXT("button"),"����Ϸ",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
		90, 60, 100, 30,hWnd, (HMENU)BTNSTAR, hInst, NULL);
	hBtnLoad=CreateWindow(TEXT("button"),"������Ϸ",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
		90, 120, 100, 30,hWnd, (HMENU)BTNLOAD, hInst, NULL);
	hBtnAbout=CreateWindow(TEXT("button"),"��Ϸ˵��",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
		90, 180, 100, 30,hWnd, (HMENU)BTNABUT, hInst, NULL);
	hBtnQuit=CreateWindow(TEXT("button"),"�˳�",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
		90, 350, 100, 30,hWnd, (HMENU)BTNQUIT, hInst, NULL);
}

//����Ϸ˵�����Ի���ĶԻ�����̺���
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}

//���¡�����Ϸ��ʱ
void OnNewGame(HWND hWnd)
{
	int chc=DialogBox(hInst, (LPCTSTR)IDD_NGDlg, hWnd, (DLGPROC)NGDlgProc);
	int spdchc=chc%10;
	int mapchc=chc/10;
	if(chc!=0){
		if(spdchc>SPDLEVEL){
			MessageBox(hWnd,"��ѡ����ٶ�δ����","����",MB_OK|MB_ICONWARNING);
		}
		else if(mapchc>maps){
			MessageBox(hWnd,"��ѡ��ĵ�ͼδ����","����",MB_OK|MB_ICONWARNING);
		}
		else if(0!=LoadMap(mapchc-1)){
			speed=rate[chc%10-1];
			OnStart(hWnd);
		}
		else {
			MessageBox(hWnd,"����ȱ�ٴ˵�ͼ����Ϣ���ͼ��ʽ���Ϸ�","����",MB_OK|MB_ICONWARNING);
		}
	}
}

//����Ϸ���á��Ի���ĶԻ�����̺���
LRESULT CALLBACK NGDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	switch (message)
	{
		case WM_INITDIALOG:
			{
				CenterDialog(hDlg);
				char bufstr[4];
				HWND hCBSpeed=GetDlgItem(hDlg, IDC_COMBSP);
				for(int i=1;i<=SPDLEVEL;i++){
					sprintf(bufstr,"%d",i);
					ComboBox_AddString(hCBSpeed, bufstr);
				}
				ComboBox_SetCurSel(hCBSpeed, 0);
				HWND hLBMaps=GetDlgItem(hDlg, IDC_MAPLIST);
				maps=GetPrivateProfileInt("General","Maps",1,".\\snake.ini");
				char mapname[INIKVLEN]={0};
				for(int j=0;j<maps;j++){
					sprintf(bufstr,"%d",j);
					GetPrivateProfileString("Maps",bufstr,"INFO LOST!",mapname,INIKVLEN,".\\snake.ini");
					ListBox_AddString(hLBMaps,mapname);
				}
				ListBox_SetCurSel(hLBMaps,0);
			}
			return TRUE;
		case WM_COMMAND:
			if (LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg,0);
				return TRUE;
			}
			else if(LOWORD(wParam) == IDOK)
			{
				HWND hCBSpeed=GetDlgItem(hDlg, IDC_COMBSP);
				HWND hLBMaps=GetDlgItem(hDlg, IDC_MAPLIST);
				int spdchc=ComboBox_GetCurSel(hCBSpeed);
				int mapchc=ListBox_GetCurSel(hLBMaps);
				EndDialog(hDlg,spdchc+1+10*(mapchc+1));
				return TRUE;
			}
			break;
	}
    return FALSE;
}

//��ʽ��ʼ��Ϸʱ
void OnStart(HWND hWnd)
{
	RECT crc,wrc;
	GetClientRect(hWnd,&crc);
	GetWindowRect(hWnd,&wrc);
	int borderwidth=(wrc.right-wrc.left)-(crc.right-crc.left);
	int borderheight=(wrc.bottom-wrc.top)-(crc.bottom-crc.top);
	ShowWindow(hBtnLoad,SW_HIDE);
	ShowWindow(hBtnStart,SW_HIDE);
	ShowWindow(hBtnAbout,SW_HIDE);
	ShowWindow(hBtnQuit,SW_HIDE);
	surf=InGame;
	MoveWindow(hWnd,wrc.left,wrc.top,col*WIDTH+borderwidth,row*HEIGHT+borderheight,true);
	init_snake();
	Init_Paint(col*WIDTH,row*HEIGHT,hWnd);
	SetTimer(hWnd,1,speed,NULL);
}

//̰ʳ�ߵĳ�ʼ��
void init_snake()
{
	int n;
	s0.len=2;
/*	s0.m_pos[0].x=0;
	s0.m_pos[0].y=0;
	s0.m_direction=RIGHTDRC;*/
	if(UPDRC==s0.m_direction)
	{
		s0.m_pos[1].x=s0.m_pos[0].x;
		s0.m_pos[1].y=(s0.m_pos[0].y+1)%row;
	}
	else if(RIGHTDRC==s0.m_direction)
	{
		s0.m_pos[1].y=s0.m_pos[0].y;
		if(s0.m_pos[0].x==0){
			s0.m_pos[1].x=col-1;
		}
		else {
			s0.m_pos[1].x=s0.m_pos[0].x-1;
		}
	}
	else if(DOWNDRC==s0.m_direction)
	{
		s0.m_pos[1].x=s0.m_pos[0].x;
		if(s0.m_pos[0].y==0){
			s0.m_pos[1].y=row-1;
		}
		else {
			s0.m_pos[1].y=s0.m_pos[0].y-1;
		}
	}
	else if(LEFTDRC==s0.m_direction)
	{
		s0.m_pos[1].y=s0.m_pos[0].y;
		s0.m_pos[1].x=(s0.m_pos[0].x+1)%col;
	}
	for(n=s0.len;n<MAXVSIZE*MAXHSIZE;n++)
	{
		s0.m_pos[n].x=-1;
		s0.m_pos[n].y=-1;
	}
	
	generateFood();
}

//����ʳ��
void generateFood()
{
	int i=0;
	srand(time(NULL));
	do{
		m_food.x=(rand()+i)%col;
		i++;
		m_food.y=(rand()+i)%row;
	}
	while(isBrick(m_food) || isSnakeB(m_food) || (m_food.x==s0.m_pos[0].x && m_food.y==s0.m_pos[0].y));
}

//�ж�һ�����Ƿ��������غ�
BOOL isSnakeB(POINT coord){
	int i;
	for(i=1;i<s0.len;i++){
		if(coord.x==s0.m_pos[i].x && coord.y==s0.m_pos[i].y){
			return TRUE;
		}
	}
	return FALSE;
}

//�ж�һ�����Ƿ���ǽ���غ�
BOOL isBrick(POINT coord){
	int i;
	for(i=0;i<bricks;i++){
		if(coord.x==m_brick[i].x && coord.y==m_brick[i].y){
			return TRUE;
		}
	}
	return FALSE;
}

//��ʼ������
void Init_Paint(int x,int y,HWND hWnd){
   hdc=GetDC(hWnd);
   bufdc=CreateCompatibleDC(hdc);
   HBITMAP bmp=CreateCompatibleBitmap(hdc,x,y);
   SelectObject(bufdc,bmp);
// MyPaint();
   DeleteObject(bmp);
}

//������Ϸ��
void MyPaint(HDC hdc)
{
	HBRUSH hbr=CreateSolidBrush(RGB(128,64,0));
	SelectObject(bufdc,hbr);
	for(int y=0;y<row;y++)  //���Ʊ���
	{
		for(int x=0;x<col;x++)
		{
			Rectangle(bufdc,x*WIDTH,y*HEIGHT,(x+1)*WIDTH,(y+1)*HEIGHT);
		}
	}
	DeleteObject(hbr);
	HBRUSH hbrred=CreateSolidBrush(RGB(255,0,0));
	SelectObject(bufdc,hbrred);
	Rectangle(bufdc,s0.m_pos[0].x*WIDTH,s0.m_pos[0].y*HEIGHT,(s0.m_pos[0].x+1)*WIDTH,(s0.m_pos[0].y+1)*HEIGHT);  //������ͷ
	DeleteObject(hbrred);
	HBRUSH hbrdgreen=CreateSolidBrush(RGB(0,128,0));
	SelectObject(bufdc,hbrdgreen);
	for(int n=1;n<s0.len;n++)  //��������
	{
		Rectangle(bufdc,s0.m_pos[n].x*WIDTH,s0.m_pos[n].y*HEIGHT,(s0.m_pos[n].x+1)*WIDTH,(s0.m_pos[n].y+1)*HEIGHT);
	}
	DeleteObject(hbrdgreen);
	HBRUSH hbrgreen=CreateSolidBrush(RGB(0,255,0));
	SelectObject(bufdc,hbrgreen);
	Rectangle(bufdc,m_food.x*WIDTH,m_food.y*HEIGHT,(m_food.x+1)*WIDTH,(m_food.y+1)*HEIGHT);  //����ʳ��
	DeleteObject(hbrgreen);
	HBRUSH hbrgrey=CreateSolidBrush(RGB(128,128,128));
	SelectObject(bufdc,hbrgrey);
	for(int j=0;j<bricks;j++)  //����ǽ
	{
		Rectangle(bufdc,m_brick[j].x*WIDTH,m_brick[j].y*HEIGHT,(m_brick[j].x+1)*WIDTH,(m_brick[j].y+1)*HEIGHT);  
	}
	DeleteObject(hbrgrey);
	//����Ҫ���Ƶ����ж���������bufdc������bmpͼ��
	//Ȼ���bufdc�ϵĶ������Ƶ�hdc��
	BitBlt(hdc,0,0,col*WIDTH,row*HEIGHT,bufdc,0,0,SRCCOPY);
}

//�������˵�
void backMenu(HWND hWnd)
{
	RECT wrc;
	GetWindowRect(hWnd,&wrc);
	surf=InMenu;
	MoveWindow(hWnd,wrc.left,wrc.top,MENUWIDTH,MENUHEIGHT,true);
	InvalidateRect(hWnd,NULL,TRUE);
	ShowWindow(hBtnLoad,SW_RESTORE);
	ShowWindow(hBtnStart,SW_RESTORE);
	ShowWindow(hBtnAbout,SW_RESTORE);
	ShowWindow(hBtnQuit,SW_RESTORE);
}

//���¡�Esc����ʱ���ֵĶԻ���ĶԻ�����̺���
LRESULT CALLBACK EscDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
//	static HWND hStatic;
	static TCHAR bufstr[15]={0};
	switch (message)
	{
		case WM_INITDIALOG:
			CenterDialog(hDlg);
		//	hStatic=GetDlgItem(hDlg,IDC_STATIC);
			sprintf(bufstr,"��ǰ�÷�Ϊ:%3d",s0.len-1);
			SetDlgItemText(hDlg,IDC_STATIC,bufstr);
			return TRUE;
		case WM_COMMAND:
			if (LOWORD(wParam)==IDCONTI) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			else if(LOWORD(wParam)==IDSAVE){
				MessageBox(hDlg,"��������δ���", "�Ժ��ٲ�", MB_OK|MB_ICONINFORMATION);
			//	EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			else if(LOWORD(wParam)==IDQUIT){
				if(IDYES==MessageBox(hDlg,"ȷ��Ҫ������Ϸ��","��ʾ",MB_YESNO|MB_ICONINFORMATION)){
					EndDialog(hDlg, LOWORD(wParam));
				}
				return TRUE;
			}
			break;
	}
    return FALSE;
}

//�����¡�Esc����ʱ
void OnEscape(HWND hWnd)
{
	KillTimer(hWnd,1);
	int chc=DialogBox(hInst, (LPCTSTR)IDD_EscDlg, hWnd, (DLGPROC)EscDlgProc);
	switch(chc)
	{
		case IDCONTI:
			SetTimer(hWnd,1,speed,NULL);
			break;
		case IDSAVE:
			break;
		case IDQUIT:
			backMenu(hWnd);
			break;
	}
}

//�Ի������
void CenterDialog(HWND hDlg)
{
	int  nWidth, nHeight, nTitleBits;
    RECT rcDialog, rcParent;
    int  xOrigin, yOrigin, xScreen, yScreen;
	
    HWND hParent = GetParent(hDlg);
	
    if(hParent == NULL)
        hParent = GetDesktopWindow();
	
    GetClientRect(hParent, &rcParent);
    ClientToScreen(hParent, (LPPOINT)&rcParent.left);  // point(left,  top)
    ClientToScreen(hParent, (LPPOINT)&rcParent.right); // point(right, bottom)
	
    // Center on Title: title bar has system menu, minimize,  maximize bitmaps
    // Width of title bar bitmaps - assumes 3 of them and dialog has a sysmenu
	// SM_CXSIZE: Width of a button in a window's caption or title bar, in pixels.
    nTitleBits = GetSystemMetrics(SM_CXSIZE);
	
    // If dialog has no sys menu compensate for odd# bitmaps by sub 1 bitwidth
    if  (!(GetWindowLong(hDlg, GWL_STYLE) & WS_SYSMENU))
        nTitleBits -= nTitleBits / 3;
	
    GetWindowRect(hDlg, &rcDialog);
    nWidth  = rcDialog.right  - rcDialog.left;
    nHeight = rcDialog.bottom - rcDialog.top;
	
	//ˮƽ����
    xOrigin = max(rcParent.right - rcParent.left - nWidth, 0)/2  + rcParent.left; // - nTitleBits;
    
	xScreen = GetSystemMetrics(SM_CXSCREEN);
	
	//�����ܷ�ֹ�Ի����Ҳ೬����Ļ��Χ
    if  (xOrigin + nWidth > xScreen)
        xOrigin = max (0, xScreen - nWidth);
	
	//��ֱ�е�ƫ��
	yOrigin = max(rcParent.bottom - rcParent.top - nHeight, 0)/3 + rcParent.top - nTitleBits;
    
	yScreen = GetSystemMetrics(SM_CYSCREEN);
    
	//�����ܷ�ֹ�Ի���ײ�������Ļ��Χ
	if  (yOrigin + nHeight > yScreen)
        yOrigin = max(0 , yScreen - nHeight);
	
    SetWindowPos(hDlg, NULL, xOrigin, yOrigin, nWidth, nHeight, SWP_NOZORDER);
}

//��ȡini�ļ��Ļ�������
void ini_data(HWND hWnd)
{
	DWORD clen=0;
	char kstr[INIKVLEN]={0};
	char vstr[INIKVLEN]={0};
	DWORD value;

//	HWND hIniDlg=CreateDialog(hInst, (LPCTSTR)IDD_INIinitDlg, hWnd, (DLGPROC)INIinitDlgProc);
//	ShowWindow(hIniDlg, SW_SHOW );

	clen=GetPrivateProfileString("General","Initialized","",vstr,2,".\\snake.ini");
	value=atol(vstr);
	if(clen==0 || value!=1){
		ini_new(hWnd);
	}
	for(int i=0;i<SPDLEVEL;i++){
		char ibuf[3];
		sprintf(ibuf,"%d",i+1);
		clen=GetPrivateProfileString("Rate",ibuf,"",vstr,11,".\\snake.ini");
		if(clen==0){
			char rbuf[12];
			sprintf(rbuf,"%ld",rate[i]);
			WritePrivateProfileString("Rate",ibuf,rbuf,".\\snake.ini");
			GetPrivateProfileString("Rate",ibuf,"",vstr,11,".\\snake.ini");
		}
		value=atol(vstr);
		rate[i]=value;
	}

//	DestroyWindow(hIniDlg);
}

//�½�һ��ini�ļ���һ��������ͼ
void ini_new(HWND hWnd)
{
	const char filename[]="snake.ini"; //��ʼ��ini
	FILE *fp=fopen(filename,"wb");
	if(fp==NULL){
		MessageBox(hWnd,"��ʼ��ʧ�ܣ����ر�","����",MB_OK|MB_ICONWARNING);
		DestroyWindow(hWnd);
	}
	fprintf(fp,";=====SNAKE.INI=====\r\n");
	fprintf(fp,";There are some settings of the snake game.\r\n");
	fprintf(fp,";Do not modify this file unless you know what you're doing.\r\n");
	fprintf(fp,"\r\n[General]\r\n");
	fprintf(fp,"Initialized=1\r\n");
	fprintf(fp,"Archives=0\r\n");
	fprintf(fp,"Maps=1\r\n");
	fprintf(fp,"\r\n[Rate]\r\n");
	fprintf(fp,"1=1000\r\n");
	fprintf(fp,"2=500\r\n");
	fprintf(fp,"3=300\r\n");
	fprintf(fp,"4=150\r\n");
	fprintf(fp,"5=80\r\n");
	fprintf(fp,"\r\n[Archives]\r\n");
	fprintf(fp,"\r\n[Maps]\r\n");
	fprintf(fp,"0=Boundless(20x20)\r\n");
	fprintf(fp,"\r\n[Boundless(20x20)]\r\n");
	fprintf(fp,"File=boundless00.map\r\n");
	fprintf(fp,"Col=20\r\n");
	fprintf(fp,"Row=20\r\n");
	fprintf(fp,"Bricks=0\r\n");
	fprintf(fp,"Record=1\r\n");
	fclose(fp);
	char mapname[]="boundless00.map"; //��ʼ��һ��������ͼ
	char tmpname[]="boundless00.map.tmp";
	FILE *fp0=fopen(tmpname,"wb");
	if(fp0==NULL){
		MessageBox(hWnd,"��ʼ��ʧ�ܣ����ر�","����",MB_OK|MB_ICONWARNING);
		remove(tmpname);
		DestroyWindow(hWnd);
	}
	fprintf(fp0,"InitDirc=0;");
	fprintf(fp0,"InitPosX=10;");
	fprintf(fp0,"InitPosY=10;");
	fclose(fp0);
	if(0==encode(tmpname,mapname)){
		MessageBox(hWnd,"��ʼ��ʧ�ܣ����ر�","����",MB_OK|MB_ICONWARNING);
		remove(tmpname);
		DestroyWindow(hWnd);
	}
	remove(tmpname);
}

/*
LRESULT CALLBACK INIinitDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
			CenterDialog(hDlg);
				return TRUE;

//		case WM_COMMAND:
//			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
//			{
//				EndDialog(hDlg, LOWORD(wParam));
//				return TRUE;
//			}
//			break;
	}
    return FALSE;
}
*/

//��ini�ж�ȡ��߷ּ�¼
int ini_record()
{
	int value;
	char mapname[INIKVLEN]={0};
	char vstr[INIKVLEN]={0};
	sprintf(vstr,"%d",mapID);
	GetPrivateProfileString("Maps",vstr,"",mapname,INIKVLEN,".\\snake.ini");
	GetPrivateProfileString(mapname,"Record","1",vstr,4,".\\snake.ini");
	value=atoi(vstr);
	if(s0.len-1>value){
		value=s0.len-1;
		sprintf(vstr,"%d",value);
	}
	WritePrivateProfileString(mapname,"Record",vstr,".\\snake.ini");
	return value;
}

//���ص�ͼ
int LoadMap(int ord)
{
	char ibuf[4]={0};
	char vstr[INIKVLEN]={0};
	sprintf(ibuf,"%d",ord);
	if(0==GetPrivateProfileString("Maps",ibuf,"",vstr,INIKVLEN,".\\snake.ini"))
	{
		return 0;  //ȷ�ϱ�Ŵ���
	}
	char val[11];
	if(0==GetPrivateProfileString(vstr,"Col","",val,3,".\\snake.ini")) //��ȡcol
	{
		return 0; 
	}
	else {
		col=atoi(val);
		if(col>MAXHSIZE){
			return 0;
		}
	}
	if(0==GetPrivateProfileString(vstr,"Row","",val,3,".\\snake.ini")) //��ȡrow
	{
		return 0;
	}
	else {
		row=atoi(val);
		if(row>MAXVSIZE){
			return 0;
		}
	}
	if(0==GetPrivateProfileString(vstr,"Bricks","",val,4,".\\snake.ini")) //��ȡbricks
	{
		return 0;
	}
	else {
		bricks=atoi(val);
		if(bricks>col*row-2){
			return 0;
		}
	}
	char mapname[INIKVLEN]={0};
	if(0==GetPrivateProfileString(vstr,"File","",mapname,INIKVLEN,".\\snake.ini")) //��ȡ��ͼ�ļ���
	{
		return 0;
	}
	char tmpname[INIKVLEN];
	strncpy(tmpname,mapname,INIKVLEN);
	strncat(tmpname,".tmp",5);
	if(decode(mapname,tmpname)==0){
		remove(tmpname);
		return 0;  //����ʧ��ʱ
	}
	FILE *fp=fopen(tmpname,"rb");
	if(fp==NULL)  //�޷���ȡ��ͼ�ļ�ʱ��ͨ����û������ļ���
	{
		remove(tmpname);
		return 0;
	}
	char key[20]={0};
	int value;
	char ch;
	int flag=0 ,bxflg=0 ,byflg=0; //flag����λ��Ƿ�
	do {
		int i=0;
		value=0;
		while((ch=fgetc(fp))!='=' && ch!=EOF){
			key[i++]=ch;  //��¼����
		}
		while((ch=fgetc(fp))!=';' && isdigit(ch) && ch!=EOF){
			value=10*value+ch-48;  //��¼��ֵ
		}
		if(strncmp(key,"InitDirc",8)==0){
			if(value>4){
				fclose(fp); //�Ƿ��ķ���
				remove(tmpname);
				return 0;
			}
			s0.m_direction=value;
			flag=flag|0x01;
		}
		else if(strncmp(key,"InitPosX",8)==0){
			if(value>col){
				fclose(fp); //Խ��
				remove(tmpname);
				return 0;
			}
			s0.m_pos[0].x=value;
			flag=flag|0x02;
		}
		else if(strncmp(key,"InitPosY",8)==0){
			if(value>row){
				fclose(fp); //Խ��
				remove(tmpname);
				return 0;
			}
			s0.m_pos[0].y=value;
			flag=flag|0x04;
		}
		for(int j=0;j<bricks;j++){
			char bstr[10]={0};
			sprintf(bstr,"Brick%03dX",j);
			if(strncmp(key,bstr,9)==0){
				if(value>col){
					fclose(fp); //Խ��
					remove(tmpname);
					return 0;
				}
				m_brick[j].x=value;
				bxflg++;
			}
		}
		if(bxflg==bricks){
			flag=flag|0x08;
		}
		for(int k=0;k<bricks;k++){
			char bstr[10]={0};
			sprintf(bstr,"Brick%03dY",k);
			if(strncmp(key,bstr,9)==0){
				if(value>row){
					fclose(fp); //Խ��
					remove(tmpname);
					return 0;
				}
				m_brick[k].y=value;
				byflg++;
			}
		}
		if(byflg==bricks){
			flag=flag|0x10;
		}
		if(ch==EOF){
			fclose(fp);
			remove(tmpname);
			return 0;
		}
	}
	while(flag!=0x1f);
	fclose(fp);
	remove(tmpname);
	mapID=ord; //��¼��ǰ�ĵ�ͼ���
	return 1;
}

//�ı���루ǿ��װ�ƣ�����
int encode(char fromfile[], char tofile[]){
	FILE *fp=fopen(fromfile,"rb");
	if(fp==NULL){
		return 0;
	}
	FILE *fp0=fopen(tofile,"wb");
	if(fp0==NULL){
		fclose(fp);
		return 0;
	}
	char ch;
	while(1){
		ch=fgetc(fp);
		if(ch==EOF)
			break;
		ch=ch|0x80; //Ӣ�ĵ�ASCII����λ����0������GBK�����ֽ���λ����1
		fputc(ch,fp0);
	}
	fclose(fp);
	fclose(fp0);
	return 1;
}

//��;������
int decode(char fromfile[], char tofile[]){
	FILE *fp=fopen(fromfile,"rb");
	if(fp==NULL){
		return 0;
	}
	FILE *fp0=fopen(tofile,"wb");
	if(fp0==NULL){
		fclose(fp);
		return 0;
	}
	char ch;
	while(1){
		ch=fgetc(fp);
		if(ch==EOF)
			break;
		ch=ch&0x7f; //Ӣ�ĵ�ASCII����λ����0������GBK�����ֽ���λ����1
		fputc(ch,fp0);
	}
	fclose(fp);
	fclose(fp0);
	
	return 1;
}