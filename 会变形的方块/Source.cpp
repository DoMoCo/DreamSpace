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
                 佛祖保佑       永无BUG
*/
    
#include"Func.h"
#include"Block.h"
#include"Frame.h"
#include<cstdlib>//
#include<ctime>  //获得随机数、system()
#include<iostream>
#include<fstream>
#include<map>
#include<iomanip>
#include<Windows.h>
using namespace std;

void start_game(Frame &frame,int interface_index,int biggest_block=0)
{
	system("cls");
	srand((int)time(NULL));    //生成伪随机数 
	Block block;
	frame.frame_initial();
	int color = rand() % 7;    //生成随机颜色
	drew_interface(interface_index,color);
	frame.DrawFrame();
	int nTimer = GetTickCount();         //记录当下时间
	int LastKeyDownTime = GetTickCount();//记录按键时间
	int score = 0;                       //游戏分数
	int g_speed = 1000;                  //游戏速度1000->100
	int last_speed;                      //记录当前游戏速度，用于变速后的恢复
	int rand_block;
	if (0 == biggest_block)              //生成随机方块
		rand_block = rand() % 19;        //介于0~18 
	else
		rand_block = rand() % biggest_block;
	bool game_over = false;              //游戏结束标志
	bool fast_mode = false;              //神速模式标志
	while (!game_over)
	{
		int next_block;
		if (0 == biggest_block)
			next_block = rand() % 19;    //介于0~18 
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
			if ((signed)GetTickCount() - nTimer >= g_speed)//下落检测
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
						g_speed = 1000 - (score / 50) * 100;//设置方块下落速度
					if (g_speed < 100)
						g_speed = 100;
					SetConsor(WINDOW_WIDTH + 30, LENGTH / 2 + 3);
					cout << "SPEED";
					SetConsor(WINDOW_WIDTH + 31, LENGTH / 2 + 4);
					cout << setw(4) << 11 - g_speed / 100;
					break;
				}
			}
			if (GetTickCount() - LastKeyDownTime >= 100)//按键频率控制
			{//变形判断任有问题，下方会有位置跳动
				LastKeyDownTime = GetTickCount();
				Pos pos, pos_temp;    //记录方块位置
				int temp = rand_block;//记录改变前的方块
				int num = 0;          //记录纠正位置次数，若大于2则变形失败
				if (GetAsyncKeyState(VK_UP))//方块旋转
				{
					change_block(-1, rand_block);
					pos = block.Get_pos();
					pos_temp = pos;
					block.Drew_override_Block(frame);
					if (!frame.JudgeMove(block, rand_block, 0, 0, -1))
						rand_block = temp;//如果变形后有方块重叠
					else
					{
						while (!frame.JudgeMove(block, rand_block, 0, 0) && num <= 2)
						{  //防止变形后重叠(边上变形时)
							if (pos.x > 5)
								block.Change_pos(-1, 0);
							if (pos.x < 5)
								block.Change_pos(1, 0);
							num++;
						}
						if (num == 3)
						{
							rand_block = temp;//回到之前的方块
							block.Change_pos(pos_temp.x - pos.x, 0);//回到之前的位置
						}
					}
					block.Drew_override_Block(frame, rand_block);
				}
				if (GetAsyncKeyState(VK_LEFT))//方向左键
				{
					if (frame.JudgeMove(block, rand_block, -1, 0))
					{
						block.Drew_override_Block(frame);
						block.Change_pos(-1, 0);
						block.Drew_override_Block(frame, rand_block);
					}
				}
				if (GetAsyncKeyState(VK_RIGHT))//方向右键
				{
					if (frame.JudgeMove(block, rand_block, 1, 0))
					{
						block.Drew_override_Block(frame);
						block.Change_pos(1, 0);
						block.Drew_override_Block(frame, rand_block);
					}
				}
				if (GetAsyncKeyState(VK_SPACE) ||GetAsyncKeyState(VK_DOWN))
				{//空格键||方向下键
					block.Drew_override_Block(frame);
					while (frame.JudgeMove(block, rand_block, 0, 1))
					{
						block.Change_pos(0, 1);
					}
					block.Drew_override_Block(frame, rand_block);
				}
				if (GetAsyncKeyState(VK_RETURN))//回车键
				{
					SetConsor(WINDOW_WIDTH + 8, LENGTH / 2);
					cout << "暂停中...";
					Sleep(150);
					while (1)
					{
						if (GetAsyncKeyState(VK_RETURN))
						{
							SetConsor(WINDOW_WIDTH + 8, LENGTH / 2);
							cout << "游戏继续 ";
							Sleep(150);//为手松开提供时间
							break;
						}
					}
				}
				if (GetAsyncKeyState(VK_ESCAPE))//Esc键
				{
					game_over = true;
					break;
				}
				if (GetAsyncKeyState(VK_SHIFT))//Shift键
					g_speed = 250;
				if (GetAsyncKeyState(VK_MENU) )//Alt键
				{
					SetConsor(WINDOW_WIDTH + 6, LENGTH / 2);
					if (fast_mode)
					{
						fast_mode = false;
						g_speed = last_speed;
						cout << "退出神速模式";
					}	
					else
					{
						cout << "进入神速模式";
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
		if (GetAsyncKeyState(VK_ESCAPE))//按ESC键回到主选单
			break;
	Sleep(100);//防止Esc作用到主菜单的判断
	system("cls");
	display_main_menu();
}

void game_description()//游戏说明
{
	SetConsor(52, 9);
	cout << " ─";
	Sleep(100);
	cout << "─";
	Sleep(100);
	cout << "─";
	Sleep(100);
	cout << "─";
	Sleep(100);
	cout << "┐";
	int ix = 1;
	for (; ix < 5; ix++)
	{
		SetConsor(61, 9 + ix);
		cout << "│";
		Sleep(100);
	}
	SetConsor(61, 9 + ix);
	cout << "┴";
	SetConsor(2, 15);
	cout << " 选项相关——1、↑上移选项卡         游戏相关——1、↑ 逆时针旋转方块 ";
	SetConsor(2, 16);
	cout << "             2、↓下移选项卡                     2、←→ 左右移动方块 ";
	SetConsor(2, 17);
	cout << "             3、空格键/回车键   选中             3、↓ / 空格键    快速沉底 ";
	SetConsor(2, 18);
	cout << "             4、Esc键   退出当前界面             4、Enter键  游戏 开始/暂停 ";
	SetConsor(2, 19);
	cout << "             5、休闲模式不计入排行榜             5、Shift键  本次 快速 下落 ";
	SetConsor(2, 20);
	cout << "             6、NULL                             6、Alt键 神速模式开启/关闭 ";

}

void high_scores(Frame &frame)//分数排行榜
{
	int ix = 1;
	for (; ix < 9; ++ix)
	{
		SetConsor(41-2*ix, 7);
		cout << "─";
		Sleep(100);
	}
	Sleep(100);
	SetConsor(41-2*ix, 7);
	cout << "├";
	frame.display_score();
}

void game_joke()//神奇模式——这是个恶作剧
{
	SetConsor(33, 17);
	cout << "正在进入神奇模式";
	Sleep(1000);
	cout << ".";
	Sleep(1000);
	cout << ".";
	Sleep(1000);
	cout << ".";
	Sleep(8000);
	SetConsor(25, 17);
	cout << "游戏太神奇，游戏包小大，请耐心等待！";
	Sleep(8000);
	SetConsor(23, 17);
	cout << "\a网络连接错误，请检测你的网络设置！！！  ";
	Sleep(3000);
	system("cls");
	display_main_menu();
}
void game_mode(Frame &frame)//选择游戏模式
{
	int pos = 1;
	bool end_it = false;
	display_mode_menu();
	char ch = ' ';
	ch = enter_judge(pos, 5, replay_mode_menu);
	switch (ch)
	{
	case'1':start_game(frame,1); break;//缭乱模式
	case'2':start_game(frame,2); break;//炫丽模式
	case'3':start_game(frame,3); break;//简洁模式
	case'4':start_game(frame,2, 3); break;//休闲模式
	case'5':game_joke(); break;  //神奇模式
	case'6':system("cls");
		    display_main_menu(); //退出当前界面
	}
}
int main()
{
	HideConsor();
	ofstream addfile("SCORE.dat", ios_base::app);//添加排行榜数据文件
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
		case'1':game_mode(frame); frame.save_score_data(); break;  //游戏开始
		case'2':high_scores(frame); break;//排行榜
 		case'3':game_description(); break;//游戏说明
		case'4':                          //退出游戏
		case'5':end_it = true;
		}
	} while (!end_it);
	return 0;
}
