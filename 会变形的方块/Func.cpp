#include "Func.h"
#include<iostream>
#include<Windows.h>
#include<cstdlib>//system()
#include<vector>
#include<string>
#include<iomanip>
#include<conio.h>
using namespace std;

void SetConsor(short x,short y)
{
	HANDLE g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//取得输出窗口句柄
	COORD cd = { x, y };
	SetConsoleCursorPosition(g_hOutput, cd);//设置光标位置
}

void HideConsor()
{
	HANDLE g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//取得句柄(获得操作权)
	CONSOLE_CURSOR_INFO cursor_info;
	cursor_info.bVisible = FALSE;//光标不可见
	cursor_info.dwSize = 100;//光标大小为100
	SetConsoleCursorInfo(g_hOutput, &cursor_info);//设置控制台光标信息
}

void ShowConsor()
{
	HANDLE g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//取得句柄(获得操作权)
	CONSOLE_CURSOR_INFO cursor_info;
	cursor_info.bVisible = TRUE;//光标可见
	cursor_info.dwSize = 20;//光标大小为100
	SetConsoleCursorInfo(g_hOutput, &cursor_info);//设置控制台光标信息
}


void change_block(int x, int &rand_block)
{
	switch (rand_block)
	{
	case 0:break;
	case 1:
	case 3:
	case 5:rand_block += 1;
		   break;
	case 2:
	case 4:
	case 6:rand_block -= 1;
		   break;
	case 7:
	case 11:
	case 15:if (x < 0)
		    rand_block += 3;
			else
				rand_block += 1;
		    break;
	case 10:
	case 14:
	case 18:if (x < 0)
			    rand_block -= 1;
			else
				rand_block -= 3;
		    break;
	case 8:
	case 9:
	case 12:
	case 13:
	case 16:
	case 17:rand_block += x; break;	
	}
}

void drew_interface(const int mode,int color_index)
{
	int color = color_index;
	int color_temp = color_index;
	vector<WORD> fore_color//前景色
	{
		FOREGROUND_RED,FOREGROUND_GREEN,FOREGROUND_BLUE,FOREGROUND_RED | FOREGROUND_GREEN,
		FOREGROUND_GREEN | FOREGROUND_BLUE,FOREGROUND_RED | FOREGROUND_BLUE,
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
	};
	vector<WORD> back_color//背景色
	{
		BACKGROUND_RED,BACKGROUND_GREEN,BACKGROUND_BLUE,BACKGROUND_RED | BACKGROUND_GREEN,
		BACKGROUND_GREEN | BACKGROUND_BLUE,BACKGROUND_RED | BACKGROUND_BLUE,
		BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
	};
//绘制上侧——
	SetConsor(WINDOW_WIDTH, WINDOW_LENGTH);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
	cout << "┏";
	for (int i = 1; i < WIDTH - 1; ++i)
	{
		if (mode!=2)
			color = i % 7;
		if (3 == mode)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
				fore_color[color]);
		else
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
				back_color[color]);
		cout << "━";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
	cout << "┳";
	for (int i = 1; i < 9; ++i)
	{
		if (mode != 2)
			color = i % 7;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
				fore_color[color]);
		cout << "━";
	}	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
	cout << "┓";
//绘制下侧——
	SetConsor(WINDOW_WIDTH, WINDOW_LENGTH + LENGTH - 1);
	cout << "┗";
	for (int i = 1; i < WIDTH - 1; ++i)
	{
		if (mode != 2)
			color = i % 7;
		if (3 == mode)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
				fore_color[color]);
		else
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
				back_color[color]);
		cout << "━";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
	cout << "┻";
	for (int i = 1; i < 9; ++i)
	{
		if (mode != 2)
			color = i % 7;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
				fore_color[color]);
		cout << "━";
	}
//绘制左右边侧| | |	
	for (int i = 1; i < LENGTH - 1; ++i)
	{
		if (mode != 2)
			color = i % 7;
		if (3 == mode)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
				fore_color[color]);
		else
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY |
				back_color[color]);
		SetConsor(WINDOW_WIDTH, WINDOW_LENGTH + i);
		cout << "┃";
		SetConsor(WINDOW_WIDTH + WIDTH * 2 - 2, WINDOW_LENGTH + i);
		cout << "┃";	
	}
	for (int i = 1; i < LENGTH - 1; ++i)
	{
		if (mode!=2)
			color = i % 7;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
				fore_color[color]);
		SetConsor(WINDOW_WIDTH + WIDTH * 2 + 16, WINDOW_LENGTH + i);
		cout << "┃";
	}
	SetConsor(WINDOW_WIDTH + WIDTH * 2 + 16, WINDOW_LENGTH + LENGTH - 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
	cout << "┛";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//恢复本色
	SetConsor(WINDOW_WIDTH + 30, LENGTH / 2);
	cout << "SCORE";
	SetConsor(WINDOW_WIDTH + 31, LENGTH / 2 + 1);
	cout << setw(4) << 0;
	SetConsor(WINDOW_WIDTH + 30, LENGTH / 2 + 3);
	cout << "SPEED";
	SetConsor(WINDOW_WIDTH + 31, LENGTH / 2 + 4);
	cout << setw(4) << 1;
	SetConsor(WINDOW_WIDTH + 25, LENGTH / 2 + 8);
	cout << "Verion 1.0.0.1";
	SetConsor(WINDOW_WIDTH + 25, LENGTH / 2 + 10);
	cout << "Powered by DMC";
}

void display_main_menu()
{
	SetConsor(34, 1);
	cout << "> 会变形的方块 <";
	SetConsor(33, 3);
	cout << "┏━━━━━━━┓";
	SetConsor(33, 5);
	cout << "┃  ＞ 开始游戏 ┃";
	SetConsor(33, 7);
	cout << "┃  排行榜      ┃";
	SetConsor(33, 9);
	cout << "┃  游戏说明    ┃";
	SetConsor(33, 11);
	cout << "┃  退出游戏    ┃";
	SetConsor(33, 13);
	cout << "┗━━━━━━━┛";
	for (short ix = 4; ix < 13; ix += 2)
	{
		SetConsor(33, ix);
		cout << "┇              ┇";
	}
}

void display_mode_menu()
{
	system("cls");
	SetConsor(34, 1);
	cout << "> 选择游戏模式 <";
	SetConsor(33, 3);
	cout << "┏━━━━━━━┓";
	SetConsor(33, 5);
	cout << "┃  ＞ 缭乱模式 ┃";
	SetConsor(33, 7);
	cout << "┃  炫丽模式    ┃";
	SetConsor(33, 9);
	cout << "┃  简洁模式    ┃";
	SetConsor(33, 11);
	cout << "┃  休闲模式    ┃";
	SetConsor(33, 13);
	cout << "┃  神奇模式    ┃";
	SetConsor(33, 15);
	cout << "┗━━━━━━━┛";
	for (short ix = 4; ix < 15; ix += 2)
	{
		SetConsor(33, ix);
		cout << "┇              ┇";
	}
}

void replay_main_menu(int last_pos, int new_pos)
{
	SetConsor(37, last_pos * 2 + 3);
	cout << "                    ";//用空格覆盖原有内容
	SetConsor(37, last_pos * 2 + 3);
	if (1 == last_pos)
		cout << "开始游戏    ┃";
	else if (2 == last_pos)
	{
		SetConsor(31, last_pos * 2 + 3);
		cout << "  ┃  ";
		cout << "排行榜      ┃";
	}
		
	else if (3 == last_pos)
		cout << "游戏说明    ┃";
	else
		cout << "退出游戏    ┃";
	SetConsor(37, new_pos * 2 + 3);
	cout << "           ";
	SetConsor(37, new_pos * 2 + 3);
	if (1 == new_pos)
		cout << "    ＞ 开始游戏";
	else if (2 == new_pos)
		cout << "    ＞ 排 行 榜";
	else if (3 == new_pos)
		cout << "    ＞ 游戏说明";
	else
		cout << "    ＞ 退出游戏";
}

void replay_mode_menu(int last_pos, int new_pos)
{
	SetConsor(37, last_pos * 2 + 3);
	cout << "               ";//用空格覆盖原有内容
	SetConsor(37, last_pos * 2 + 3);
	if (1 == last_pos)
		cout << "缭乱模式    ┃";
	else if (2 == last_pos)
		cout << "炫丽模式    ┃";
	else if (3 == last_pos)
		cout << "简洁模式    ┃";
	else if (4 == last_pos)
		cout << "休闲模式    ┃";
	else
		cout << "神奇模式    ┃";
	SetConsor(37, new_pos * 2 + 3);
	cout << "           ";
	SetConsor(37, new_pos * 2 + 3);
	if (1 == new_pos)
		cout << "    ＞ 缭乱模式";
	else if (2 == new_pos)
		cout << "    ＞ 炫丽模式";
	else if (3 == new_pos)
		cout << "    ＞ 简洁模式";
	else if(4==new_pos)
		cout << "    ＞ 休闲模式";
	else
		cout << "    ＞ 神奇模式";

}


char enter_judge( int &beg_pos,int end_pos,void (*replay)(int,int))//返回选择的函数
{
	bool display = false;
	int last_pos = beg_pos;
	char func = ' ';
	int LastKeyDownTime = GetTickCount();
	while (1)
	{
		if (GetTickCount() - LastKeyDownTime >=100)
		{
			LastKeyDownTime = GetTickCount();
			if (GetAsyncKeyState(VK_UP))//方向上键，选择框上移
			{
				display = true;
				if (beg_pos > 1)         
					beg_pos--;
				else
					beg_pos = end_pos;
			}
			if (GetAsyncKeyState(VK_DOWN))//方向下键，选择框下移
			{
				display = true;
				if (beg_pos < end_pos)
					beg_pos++;
				else
					beg_pos = 1;
			}
			if (GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState(VK_RETURN) & 0x8000)
			{  //空格和回车键，选中选项
				func = beg_pos + 48;
				Sleep(150);//防止判断按键失误(按一次误判为两次)
				break;
			}
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)//Esc键
			{  
				func = end_pos + 48+1;
				Sleep(100);
				break;
			}
			if (display)
			{
				(*replay)(last_pos,beg_pos);
				last_pos = beg_pos;
				display = false;
			}
		}
	}	
	return func;
}

