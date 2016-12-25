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
	HANDLE g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//ȡ��������ھ��
	COORD cd = { x, y };
	SetConsoleCursorPosition(g_hOutput, cd);//���ù��λ��
}

void HideConsor()
{
	HANDLE g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//ȡ�þ��(��ò���Ȩ)
	CONSOLE_CURSOR_INFO cursor_info;
	cursor_info.bVisible = FALSE;//��겻�ɼ�
	cursor_info.dwSize = 100;//����СΪ100
	SetConsoleCursorInfo(g_hOutput, &cursor_info);//���ÿ���̨�����Ϣ
}

void ShowConsor()
{
	HANDLE g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//ȡ�þ��(��ò���Ȩ)
	CONSOLE_CURSOR_INFO cursor_info;
	cursor_info.bVisible = TRUE;//���ɼ�
	cursor_info.dwSize = 20;//����СΪ100
	SetConsoleCursorInfo(g_hOutput, &cursor_info);//���ÿ���̨�����Ϣ
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
	vector<WORD> fore_color//ǰ��ɫ
	{
		FOREGROUND_RED,FOREGROUND_GREEN,FOREGROUND_BLUE,FOREGROUND_RED | FOREGROUND_GREEN,
		FOREGROUND_GREEN | FOREGROUND_BLUE,FOREGROUND_RED | FOREGROUND_BLUE,
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
	};
	vector<WORD> back_color//����ɫ
	{
		BACKGROUND_RED,BACKGROUND_GREEN,BACKGROUND_BLUE,BACKGROUND_RED | BACKGROUND_GREEN,
		BACKGROUND_GREEN | BACKGROUND_BLUE,BACKGROUND_RED | BACKGROUND_BLUE,
		BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
	};
//�����ϲࡪ��
	SetConsor(WINDOW_WIDTH, WINDOW_LENGTH);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
	cout << "��";
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
		cout << "��";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
	cout << "��";
	for (int i = 1; i < 9; ++i)
	{
		if (mode != 2)
			color = i % 7;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
				fore_color[color]);
		cout << "��";
	}	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
	cout << "��";
//�����²ࡪ��
	SetConsor(WINDOW_WIDTH, WINDOW_LENGTH + LENGTH - 1);
	cout << "��";
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
		cout << "��";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
	cout << "��";
	for (int i = 1; i < 9; ++i)
	{
		if (mode != 2)
			color = i % 7;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
				fore_color[color]);
		cout << "��";
	}
//�������ұ߲�| | |	
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
		cout << "��";
		SetConsor(WINDOW_WIDTH + WIDTH * 2 - 2, WINDOW_LENGTH + i);
		cout << "��";	
	}
	for (int i = 1; i < LENGTH - 1; ++i)
	{
		if (mode!=2)
			color = i % 7;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
				fore_color[color]);
		SetConsor(WINDOW_WIDTH + WIDTH * 2 + 16, WINDOW_LENGTH + i);
		cout << "��";
	}
	SetConsor(WINDOW_WIDTH + WIDTH * 2 + 16, WINDOW_LENGTH + LENGTH - 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
	cout << "��";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//�ָ���ɫ
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
	cout << "> ����εķ��� <";
	SetConsor(33, 3);
	cout << "������������������";
	SetConsor(33, 5);
	cout << "��  �� ��ʼ��Ϸ ��";
	SetConsor(33, 7);
	cout << "��  ���а�      ��";
	SetConsor(33, 9);
	cout << "��  ��Ϸ˵��    ��";
	SetConsor(33, 11);
	cout << "��  �˳���Ϸ    ��";
	SetConsor(33, 13);
	cout << "������������������";
	for (short ix = 4; ix < 13; ix += 2)
	{
		SetConsor(33, ix);
		cout << "��              ��";
	}
}

void display_mode_menu()
{
	system("cls");
	SetConsor(34, 1);
	cout << "> ѡ����Ϸģʽ <";
	SetConsor(33, 3);
	cout << "������������������";
	SetConsor(33, 5);
	cout << "��  �� ����ģʽ ��";
	SetConsor(33, 7);
	cout << "��  ����ģʽ    ��";
	SetConsor(33, 9);
	cout << "��  ���ģʽ    ��";
	SetConsor(33, 11);
	cout << "��  ����ģʽ    ��";
	SetConsor(33, 13);
	cout << "��  ����ģʽ    ��";
	SetConsor(33, 15);
	cout << "������������������";
	for (short ix = 4; ix < 15; ix += 2)
	{
		SetConsor(33, ix);
		cout << "��              ��";
	}
}

void replay_main_menu(int last_pos, int new_pos)
{
	SetConsor(37, last_pos * 2 + 3);
	cout << "                    ";//�ÿո񸲸�ԭ������
	SetConsor(37, last_pos * 2 + 3);
	if (1 == last_pos)
		cout << "��ʼ��Ϸ    ��";
	else if (2 == last_pos)
	{
		SetConsor(31, last_pos * 2 + 3);
		cout << "  ��  ";
		cout << "���а�      ��";
	}
		
	else if (3 == last_pos)
		cout << "��Ϸ˵��    ��";
	else
		cout << "�˳���Ϸ    ��";
	SetConsor(37, new_pos * 2 + 3);
	cout << "           ";
	SetConsor(37, new_pos * 2 + 3);
	if (1 == new_pos)
		cout << "    �� ��ʼ��Ϸ";
	else if (2 == new_pos)
		cout << "    �� �� �� ��";
	else if (3 == new_pos)
		cout << "    �� ��Ϸ˵��";
	else
		cout << "    �� �˳���Ϸ";
}

void replay_mode_menu(int last_pos, int new_pos)
{
	SetConsor(37, last_pos * 2 + 3);
	cout << "               ";//�ÿո񸲸�ԭ������
	SetConsor(37, last_pos * 2 + 3);
	if (1 == last_pos)
		cout << "����ģʽ    ��";
	else if (2 == last_pos)
		cout << "����ģʽ    ��";
	else if (3 == last_pos)
		cout << "���ģʽ    ��";
	else if (4 == last_pos)
		cout << "����ģʽ    ��";
	else
		cout << "����ģʽ    ��";
	SetConsor(37, new_pos * 2 + 3);
	cout << "           ";
	SetConsor(37, new_pos * 2 + 3);
	if (1 == new_pos)
		cout << "    �� ����ģʽ";
	else if (2 == new_pos)
		cout << "    �� ����ģʽ";
	else if (3 == new_pos)
		cout << "    �� ���ģʽ";
	else if(4==new_pos)
		cout << "    �� ����ģʽ";
	else
		cout << "    �� ����ģʽ";

}


char enter_judge( int &beg_pos,int end_pos,void (*replay)(int,int))//����ѡ��ĺ���
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
			if (GetAsyncKeyState(VK_UP))//�����ϼ���ѡ�������
			{
				display = true;
				if (beg_pos > 1)         
					beg_pos--;
				else
					beg_pos = end_pos;
			}
			if (GetAsyncKeyState(VK_DOWN))//�����¼���ѡ�������
			{
				display = true;
				if (beg_pos < end_pos)
					beg_pos++;
				else
					beg_pos = 1;
			}
			if (GetAsyncKeyState(VK_SPACE) || GetAsyncKeyState(VK_RETURN) & 0x8000)
			{  //�ո�ͻس�����ѡ��ѡ��
				func = beg_pos + 48;
				Sleep(150);//��ֹ�жϰ���ʧ��(��һ������Ϊ����)
				break;
			}
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)//Esc��
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

