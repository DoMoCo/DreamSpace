#include"Func.h"
#include"Block.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include "Frame.h"
#include<Windows.h>
#include<vector>
#include<iomanip>
#include<string>
using namespace std;

Frame::Frame()
{
	for (int ix = 1; ix < LENGTH; ++ix)//1->21
		_stage[ix][0] = true;          //左外围全设为true,意指此处“有方块”
	for (int ix = 1; ix < LENGTH; ++ix)//1->21
		_stage[ix][11] = true;         //右外围
	for (int ix = 1; ix < WIDTH-1; ++ix)//1->10
		_stage[21][ix] = true;         //下侧
	for (int ix = 1; ix < WIDTH - 1; ++ix)
		_stage[0][ix] = false;         //上侧1->10
	for (int i = 1; i < LENGTH - 1; ++i)   //初始化游戏区域，全为fasle，意指开始没有方块
		for (int j = 1; j < WIDTH - 1; ++j)
			_stage[i][j] = false;
	_highline = 20;
	ifstream infile("SCORE.dat");
	if (infile)
	{
		string text;
		string name;
		int score,i=0;
        while (getline(infile, text) && (!text.empty()))
		{
			istringstream line(text);
			line >> name;
			line >> score;
			_name.push_back(name);
			_score.push_back(score);
			i++;
		}
		for (; i < 10; ++i)
		{
			_name.push_back("Noname");
			_score.push_back(0);
		}
	}
	infile.close();
}

void Frame::frame_initial()
{
	for (int i = 1; i < LENGTH - 1; ++i)   //初始化游戏区域，全为fasle，意指开始没有方块
		for (int j = 1; j < WIDTH - 1; ++j)
			_stage[i][j] = false;
}

void Frame::DrawFrame()
{
	for (int i = 1; i < LENGTH-1; ++i)
	{
		SetConsor(WINDOW_WIDTH + 2, WINDOW_LENGTH + i);
		for (int j = 1; j < WIDTH-1 ; ++j)
		{
			if (_stage[i][j])
				cout << "■";
			else
				cout << "  ";
		}
	}
}

void Frame::Drew_game_over()
{
	for (int i = 1; i < LENGTH - 1; ++i)
	{
		SetConsor(WINDOW_WIDTH + 2, WINDOW_LENGTH + i);
		for (int j = 1; j < WIDTH - 1; ++j)
		{
			Sleep(20);
			cout << "■";
		}

	}
	SetConsor(WINDOW_WIDTH + 8, LENGTH / 2);
	cout << "GameOver";
	SetConsor(WINDOW_WIDTH + 4, LENGTH / 2 + 2);
	cout << "按ESC键退出游戏";
}

bool Frame::Get_info(int x, int y)
{
	if (x >= 0 && x <= LENGTH&&y>=0 && y <= WIDTH)
		return _stage[x][y];
	else
		return false;
}

int Frame::Calculate_score(Block &block)//计算分数
{
	Pos pos = block.Get_pos();
	vector<int> full_lines;//记录方块满行的行标
	int score, add = 0;
	int num_of_lines = 0;   //记录满行的行数
	bool is_full;           //记录是否有满行
	if (pos.y < 1)
		pos.y = 1;
	for (int i = pos.y; i < pos.y + 4 && i < LENGTH - 1; ++i)
	{
		is_full = true;
		for (int j = 1; j < WIDTH - 1; ++j)
			if (!(_stage[i][j]))
			{
				is_full = false;//有一处无方块即说明该行不满行，跳出
				break;
			}
		if (is_full)
		{
			num_of_lines++;
			full_lines.push_back(i);
		}
	}
	for (int i = 0; i < num_of_lines; ++i)//计算分数
		add += i;                         //0->0、1->1、2->3、3->6、4->10
	score = num_of_lines + add;
	if (full_lines.size())
		block_down(full_lines);
	return score;
}

void Frame::block_down(vector<int>& full_lines)
{
	int k = 1, sum = 1;
	while (sum <= 6)//闪烁6次
	{
		for (int i = 0; i < (int)full_lines.size(); ++i)
		{
			SetConsor(WINDOW_WIDTH + 2, WINDOW_LENGTH + full_lines[i]);//将光标置于满行的
			for (int j = 1; j < WIDTH - 1; ++j)                       //行首
				if (k % 2)//两者交替打印
					cout << "■";
				else
					cout << "  ";
		}
		sum++;
		k++;
		Sleep(80);
	}
	for (int i = 0; i < (int)full_lines.size(); ++i)
		for (int j = 1; j < WIDTH - 1; ++j)//数据归零
			_stage[full_lines[i]][j] = false;
	int line = full_lines.back() - 1;
	bool out;
	for (int i = full_lines.back(); i > _highline; --i)//从下往上数据和方块下移
	{
		for (; line > _highline; --line)               //找到有方块的离空行的最近一行
		{
			out = true;
			for (int j = 0; j < (int)full_lines.size(); ++j)//判断该行是否是满行
				if (line == full_lines[j])
				{
					out = false;                            //若是，则继续寻找
					break;
				}
			if (out)                                        //若答案为否，则找到
				break;
		}
		for (int k = 1; k < WIDTH - 1; ++k)//数据下移
		{
			_stage[i][k] = _stage[line][k];
			_stage[line][k] = false;       //清空当前行

		}
		line--; //从该行的的上一行继续下移数据和方块
	}
	DrawFrame();//重新绘制游戏区
}

bool Frame::JudgeMove( Block & block, int a_block, short x, short y,int fun)
{
	Pos pos = block.Get_pos();
	pos.x += x;
	pos.y += y;
	bool move_ok = true;
	if (0 == fun)//判断是否有方块重合，用于判断是否可以继续移动
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
			{
				if (Get_info(pos.y + i, pos.x + j)
					&& block.Get_Block(a_block, i, j))
				{
					move_ok = false;
					i = 4;
					break;
				}
			}
	}
	else//判断除边界外是否有方块重合，用于处理边界方块变形
	{
		short temp_j=0,j=0,end_j=4;
		if (pos.x < 1)
			j = 1 - pos.x;
		else if (pos.x > 6)
			end_j = 11 - pos.x;
		for (int i = 0; i < 4; ++i)
		{
			temp_j = j;
			for (; temp_j < end_j; ++temp_j)
			{
				if (Get_info(pos.y + i, pos.x + temp_j)
					&& block.Get_Block(a_block, i, temp_j))
				{
					move_ok = false;
					i = 4;
					break;
				}
			}
		}
	}
	return move_ok;
}

void Frame::save_frame(Block & block, int a_block)
{
	Pos pos = block.Get_pos();
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			if (block.Get_Block(a_block, i, j))
				Change_info(pos.y + i, pos.x + j);
		if (pos.y + i < _highline)
			_highline = pos.y + i;//更新有方块的最高行(从下往上看)
	}
}

void Frame::save_score(int score)
{
	string name;
	int end= _score.size();
	for (int ix=0; ix<end; ++ix)
	{
		if (score > _score[ix])
		{
			SetConsor(WINDOW_WIDTH + 6, LENGTH / 2);
			cout << "壮士智计无双";
			SetConsor(WINDOW_WIDTH + 3, LENGTH / 2 + 2);
			cout << "请留下大名:   \b\b\b";
			ShowConsor();
			cin >> name;
			HideConsor();
			_name.push_back(name);
			_score.push_back(score);
			int temp_score;
			string temp_name;
			end = _score.size();
			for (int i = 0; i < end - 1; ++i)//名次排序
			{
				int k = i;
				for (int j = i + 1; j < end; ++j)
					if (_score[i] < _score[j])
						k = j;
				if (k != i)
				{
					temp_score = _score[i];
					_score[i] = _score[k];
					_score[k] = temp_score;
					temp_name = _name[i];
					_name[i] = _name[k];
					_name[k] = temp_name;
				}
			}
			break;
		}
	}
}

void Frame::display_score()
{
	int end = _score.size()+1;
	for (int ix = 1; ix <= 10&&ix<end; ++ix)
	{
		SetConsor(3, 2 + ix);
		cout << "No." << setw(2) << ix
			<< setw(9) << _name[ix-1]
			<< setw(5) << _score[ix-1];
	}
}

void Frame::save_score_data()
{
	ofstream outfile("SCORE.dat");
	int end = _score.size();
	for (int ix = 0; ix < end&&ix < 10; ++ix)
		outfile << setw(8) << _name[ix]
		<< setw(6) << _score[ix] << endl;
	outfile.close();
}

