/*
                         _ooOoo_
                        o8888888o
                        88" . "88
                        (| > < |)
                        O\  o  /O
                     ____/`---'\____
                   .'  \\|     |//  `.
                  /  \\|||  :  |||//  \
                 /  _||||| -:- |||||-  \
                 |   | \\\  |  /// |   |
                 | \_|  ''\---/''  |_/ |
                 \  .-\___ `-`  ___/-. /
               ___`. .'  /--.--\  `. . ___
            ."" '<  `.___\_<:>_/___.'  >' "".
           | | :  `- \`.;`\ _ /`;.`/ - ` : | |
           \  \ `-.   \_ __\ /__ _/   .-` /  /
      ======`-.____`-.___\_____/___.-`____.-'======
                         `=---='
     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                 ���汣��       ����BUG
*/
    
#include"Func.h"
#include"Block.h"
#include"Frame.h"
#include<cstdlib>//
#include<ctime>  //����������system()
#include<iostream>
#include<fstream>
#include<map>
#include<iomanip>
#include<Windows.h>
using namespace std;

void start_game(Frame &frame,int interface_index,int biggest_block=0)
{
	system("cls");
	srand((int)time(NULL));    //����α����� 
	Block block;
	frame.frame_initial();
	int color = rand() % 7;    //���������ɫ
	drew_interface(interface_index,color);
	frame.DrawFrame();
	int nTimer = GetTickCount();         //��¼����ʱ��
	int LastKeyDownTime = GetTickCount();//��¼����ʱ��
	int score = 0;                       //��Ϸ����
	int g_speed = 1000;                  //��Ϸ�ٶ�1000->100
	int last_speed;                      //��¼��ǰ��Ϸ�ٶȣ����ڱ��ٺ�Ļָ�
	int rand_block;
	if (0 == biggest_block)              //�����������
		rand_block = rand() % 19;        //����0~18 
	else
		rand_block = rand() % biggest_block;
	bool game_over = false;              //��Ϸ������־
	bool fast_mode = false;              //����ģʽ��־
	while (!game_over)
	{
		int next_block;
		if (0 == biggest_block)
			next_block = rand() % 19;    //����0~18 
		else
			next_block = rand() % biggest_block;
		if (!frame.JudgeMove(block, next_block, 0, 0))
		{
			block.Drew_override_Block(frame, -1, 52, 3);
			break;
		}
		block.Drew_override_Block(frame, rand_block);
		block.Drew_override_Block(frame, next_block, 52, 3);
		while (true)
		{
			if ((signed)GetTickCount() - nTimer >= g_speed)//������
			{
				nTimer = GetTickCount();
				if (frame.JudgeMove(block, rand_block, 0, 1))
				{
					block.Drew_override_Block(frame);
					block.Change_pos(0, 1);
					block.Drew_override_Block(frame, rand_block);
				}
				else
				{
					frame.save_frame(block, rand_block);
					score += frame.Calculate_score(block);
					block.Change_pos(-1, -1);
					SetConsor(WINDOW_WIDTH + 30, LENGTH / 2);
					cout << "SCORE";
					SetConsor(WINDOW_WIDTH + 31, LENGTH / 2 + 1);
					cout << setw(4) << score;
					if(!fast_mode)
						g_speed = 1000 - (score / 50) * 100;//���÷��������ٶ�
					if (g_speed < 100)
						g_speed = 100;
					SetConsor(WINDOW_WIDTH + 30, LENGTH / 2 + 3);
					cout << "SPEED";
					SetConsor(WINDOW_WIDTH + 31, LENGTH / 2 + 4);
					cout << setw(4) << 11 - g_speed / 100;
					break;
				}
			}
			if (GetTickCount() - LastKeyDownTime >= 100)//����Ƶ�ʿ���
			{//�����ж��������⣬�·�����λ������
				LastKeyDownTime = GetTickCount();
				Pos pos, pos_temp;    //��¼����λ��
				int temp = rand_block;//��¼�ı�ǰ�ķ���
				int num = 0;          //��¼����λ�ô�����������2�����ʧ��
				if (GetAsyncKeyState(VK_UP))//������ת
				{
					change_block(-1, rand_block);
					pos = block.Get_pos();
					pos_temp = pos;
					block.Drew_override_Block(frame);
					if (!frame.JudgeMove(block, rand_block, 0, 0, -1))
						rand_block = temp;//������κ��з����ص�
					else
					{
						while (!frame.JudgeMove(block, rand_block, 0, 0) && num <= 2)
						{  //��ֹ���κ��ص�(���ϱ���ʱ)
							if (pos.x > 5)
								block.Change_pos(-1, 0);
							if (pos.x < 5)
								block.Change_pos(1, 0);
							num++;
						}
						if (num == 3)
						{
							rand_block = temp;//�ص�֮ǰ�ķ���
							block.Change_pos(pos_temp.x - pos.x, 0);//�ص�֮ǰ��λ��
						}
					}
					block.Drew_override_Block(frame, rand_block);
				}
				if (GetAsyncKeyState(VK_LEFT))//�������
				{
					if (frame.JudgeMove(block, rand_block, -1, 0))
					{
						block.Drew_override_Block(frame);
						block.Change_pos(-1, 0);
						block.Drew_override_Block(frame, rand_block);
					}
				}
				if (GetAsyncKeyState(VK_RIGHT))//�����Ҽ�
				{
					if (frame.JudgeMove(block, rand_block, 1, 0))
					{
						block.Drew_override_Block(frame);
						block.Change_pos(1, 0);
						block.Drew_override_Block(frame, rand_block);
					}
				}
				if (GetAsyncKeyState(VK_SPACE) ||GetAsyncKeyState(VK_DOWN))
				{//�ո��||�����¼�
					block.Drew_override_Block(frame);
					while (frame.JudgeMove(block, rand_block, 0, 1))
					{
						block.Change_pos(0, 1);
					}
					block.Drew_override_Block(frame, rand_block);
				}
				if (GetAsyncKeyState(VK_RETURN))//�س���
				{
					SetConsor(WINDOW_WIDTH + 8, LENGTH / 2);
					cout << "��ͣ��...";
					Sleep(150);
					while (1)
					{
						if (GetAsyncKeyState(VK_RETURN))
						{
							SetConsor(WINDOW_WIDTH + 8, LENGTH / 2);
							cout << "��Ϸ���� ";
							Sleep(150);//Ϊ���ɿ��ṩʱ��
							break;
						}
					}
				}
				if (GetAsyncKeyState(VK_ESCAPE))//Esc��
				{
					game_over = true;
					break;
				}
				if (GetAsyncKeyState(VK_SHIFT))//Shift��
					g_speed = 250;
				if (GetAsyncKeyState(VK_MENU) )//Alt��
				{
					SetConsor(WINDOW_WIDTH + 6, LENGTH / 2);
					if (fast_mode)
					{
						fast_mode = false;
						g_speed = last_speed;
						cout << "�˳�����ģʽ";
					}	
					else
					{
						cout << "��������ģʽ";
						last_speed = g_speed;
						g_speed = 200;
						fast_mode = true;
					}
				}
			}
		}
		rand_block = next_block;
		block.Drew_override_Block(frame, -1, 52, 3);
	}
	if(0==biggest_block)
		frame.save_score(score);
	frame.Drew_game_over();
	while (1)
		if (GetAsyncKeyState(VK_ESCAPE))//��ESC���ص���ѡ��
			break;
	Sleep(100);//��ֹEsc���õ����˵����ж�
	system("cls");
	display_main_menu();
}

void game_description()//��Ϸ˵��
{
	SetConsor(52, 9);
	cout << " ��";
	Sleep(100);
	cout << "��";
	Sleep(100);
	cout << "��";
	Sleep(100);
	cout << "��";
	Sleep(100);
	cout << "��";
	int ix = 1;
	for (; ix < 5; ix++)
	{
		SetConsor(61, 9 + ix);
		cout << "��";
		Sleep(100);
	}
	SetConsor(61, 9 + ix);
	cout << "��";
	SetConsor(2, 15);
	cout << " ѡ����ء���1��������ѡ�         ��Ϸ��ء���1���� ��ʱ����ת���� ";
	SetConsor(2, 16);
	cout << "             2��������ѡ�                     2������ �����ƶ����� ";
	SetConsor(2, 17);
	cout << "             3���ո��/�س���   ѡ��             3���� / �ո��    ���ٳ��� ";
	SetConsor(2, 18);
	cout << "             4��Esc��   �˳���ǰ����             4��Enter��  ��Ϸ ��ʼ/��ͣ ";
	SetConsor(2, 19);
	cout << "             5������ģʽ���������а�             5��Shift��  ���� ���� ���� ";
	SetConsor(2, 20);
	cout << "             6��NULL                             6��Alt�� ����ģʽ����/�ر� ";

}

void high_scores(Frame &frame)//�������а�
{
	int ix = 1;
	for (; ix < 9; ++ix)
	{
		SetConsor(41-2*ix, 7);
		cout << "��";
		Sleep(100);
	}
	Sleep(100);
	SetConsor(41-2*ix, 7);
	cout << "��";
	frame.display_score();
}

void game_joke()//����ģʽ�������Ǹ�������
{
	SetConsor(33, 17);
	cout << "���ڽ�������ģʽ";
	Sleep(1000);
	cout << ".";
	Sleep(1000);
	cout << ".";
	Sleep(1000);
	cout << ".";
	Sleep(8000);
	SetConsor(25, 17);
	cout << "��Ϸ̫���棬��Ϸ��С�������ĵȴ���";
	Sleep(8000);
	SetConsor(23, 17);
	cout << "\a�������Ӵ�����������������ã�����  ";
	Sleep(3000);
	system("cls");
	display_main_menu();
}
void game_mode(Frame &frame)//ѡ����Ϸģʽ
{
	int pos = 1;
	bool end_it = false;
	display_mode_menu();
	char ch = ' ';
	ch = enter_judge(pos, 5, replay_mode_menu);
	switch (ch)
	{
	case'1':start_game(frame,1); break;//����ģʽ
	case'2':start_game(frame,2); break;//����ģʽ
	case'3':start_game(frame,3); break;//���ģʽ
	case'4':start_game(frame,2, 3); break;//����ģʽ
	case'5':game_joke(); break;  //����ģʽ
	case'6':system("cls");
		    display_main_menu(); //�˳���ǰ����
	}
}
int main()
{
	HideConsor();
	ofstream addfile("SCORE.dat", ios_base::app);//������а������ļ�
	addfile.close();
	Frame frame;
	int pos=1;
	bool end_it = false;
	display_main_menu();
	char ch;
	do
	{
		ch = ' ';
		ch = enter_judge(pos,4,replay_main_menu);
		switch (ch)
		{
		case'1':game_mode(frame); frame.save_score_data(); break;  //��Ϸ��ʼ
		case'2':high_scores(frame); break;//���а�
 		case'3':game_description(); break;//��Ϸ˵��
		case'4':                          //�˳���Ϸ
		case'5':end_it = true;
		}
	} while (!end_it);
	return 0;
}
