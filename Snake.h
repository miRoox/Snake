/*
#if !defined(AFX_SNAKE_H__2678B817_D0D4_433F_983E_2C3194AC7220__INCLUDED_)
#define AFX_SNAKE_H__2678B817_D0D4_433F_983E_2C3194AC7220__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"


#endif // !defined(AFX_SNAKE_H__2678B817_D0D4_433F_983E_2C3194AC7220__INCLUDED_)
*/


#ifndef _SNAKE
#define _SNAKE

#define  WIDTH 30  //һ��Ŀ��
#define  HEIGHT 30 //һ��ĸ߶�
#define  MAXVSIZE  20  //y��������
#define  MAXHSIZE  20  //x��������

#define INIKVLEN 50
#define INIKVNUM 500

#define UPDRC 0  //����
#define RIGHTDRC 1
#define DOWNDRC 2
#define LEFTDRC 3

#define SPDLEVEL 5

#define MENUHEIGHT 450  //���˵���С
#define MENUWIDTH 300

#define BTNSTAR 1  //��ť
#define BTNLOAD 2
#define BTNABUT 4
#define BTNQUIT 3

//-Global-

struct Snake
{
   POINT m_pos[MAXHSIZE*MAXVSIZE];
   int m_direction;
   int len;
} s0;
POINT m_food;  //ʳ��
POINT m_brick[MAXHSIZE*MAXVSIZE];  //ǽ

int mapID=0;

int bricks=0;

int row=20;  //y�����
int col=20;  //x�����

int maps=1;
int archives=0;

int speed;
long int rate[SPDLEVEL]={1000,500,300,150,80};

HWND hBtnStart,hBtnLoad,hBtnQuit,hBtnAbout;
HDC hdc ,bufdc;

enum Surface {InMenu=0,InGame} surf=InMenu;

void ini_new(HWND hWnd);
void ini_data(HWND hWnd);
int ini_record();

int LoadMap(int ord);

void OnCreateButtons(HWND hWnd);
void OnNewGame(HWND hWnd);
void OnStart(HWND hWnd);
void OnEscape(HWND hWnd);
void backMenu(HWND hWnd);

void MyPaint(HDC hdc);

void Init_Paint(int x,int y,HWND hWnd);
void init_snake();

void CenterDialog(HWND hDlg);

void generateFood();

BOOL isBrick(POINT coord);
BOOL isSnakeB(POINT coord);

LRESULT CALLBACK INIinitDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK NGDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK EscDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int encode(char fromfile[], char tofile[]);
int decode(char fromfile[], char tofile[]);

#endif