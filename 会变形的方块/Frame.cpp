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
		_stage[ix][0] = true;          //����Χȫ��Ϊtrue,��ָ�˴����з��顱
	for (int ix = 1; ix < LENGTH; ++ix)//1->21
		_stage[ix][11] = true;         //����Χ
	for (int ix = 1; ix < WIDTH-1; ++ix)//1->10
		_stage[21][ix] = true;         //�²�
	for (int ix = 1; ix < WIDTH - 1; ++ix)
		_stage[0][ix] = false;         //�ϲ�1->10
	for (int i = 1; i < LENGTH - 1; ++i)   //��ʼ����Ϸ����ȫΪfasle����ָ��ʼû�з���
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
	for (int i = 1; i < LENGTH - 1; ++i)   //��ʼ����Ϸ����ȫΪfasle����ָ��ʼû�з���
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
				cout << "��";
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
			cout << "��";
		}

	}
	SetConsor(WINDOW_WIDTH + 8, LENGTH / 2);
	cout << "GameOver";
	SetConsor(WINDOW_WIDTH + 4, LENGTH / 2 + 2);
	cout << "��ESC���˳���Ϸ";
}

bool Frame::Get_info(int x, int y)
{
	if (x >= 0 && x <= LENGTH&&y>=0 && y <= WIDTH)
		return _stage[x][y];
	else
		return false;
}

int Frame::Calculate_score(Block &block)//�������
{
	Pos pos = block.Get_pos();
	vector<int> full_lines;//��¼�������е��б�
	int score, add = 0;
	int num_of_lines = 0;   //��¼���е�����
	bool is_full;           //��¼�Ƿ�������
	if (pos.y < 1)
		pos.y = 1;
	for (int i = pos.y; i < pos.y + 4 && i < LENGTH - 1; ++i)
	{
		is_full = true;
		for (int j = 1; j < WIDTH - 1; ++j)
			if (!(_stage[i][j]))
			{
				is_full = false;//��һ���޷��鼴˵�����в����У�����
				break;
			}
		if (is_full)
		{
			num_of_lines++;
			full_lines.push_back(i);
		}
	}
	for (int i = 0; i < num_of_lines; ++i)//�������
		add += i;                         //0->0��1->1��2->3��3->6��4->10
	score = num_of_lines + add;
	if (full_lines.size())
		block_down(full_lines);
	return score;
}

void Frame::block_down(vector<int>& full_lines)
{
	int k = 1, sum = 1;
	while (sum <= 6)//��˸6��
	{
		for (int i = 0; i < (int)full_lines.size(); ++i)
		{
			SetConsor(WINDOW_WIDTH + 2, WINDOW_LENGTH + full_lines[i]);//������������е�
			for (int j = 1; j < WIDTH - 1; ++j)                       //����
				if (k % 2)//���߽����ӡ
					cout << "��";
				else
					cout << "  ";
		}
		sum++;
		k++;
		Sleep(80);
	}
	for (int i = 0; i < (int)full_lines.size(); ++i)
		for (int j = 1; j < WIDTH - 1; ++j)//���ݹ���
			_stage[full_lines[i]][j] = false;
	int line = full_lines.back() - 1;
	bool out;
	for (int i = full_lines.back(); i > _highline; --i)//�����������ݺͷ�������
	{
		for (; line > _highline; --line)               //�ҵ��з��������е����һ��
		{
			out = true;
			for (int j = 0; j < (int)full_lines.size(); ++j)//�жϸ����Ƿ�������
				if (line == full_lines[j])
				{
					out = false;                            //���ǣ������Ѱ��
					break;
				}
			if (out)                                        //����Ϊ�����ҵ�
				break;
		}
		for (int k = 1; k < WIDTH - 1; ++k)//��������
		{
			_stage[i][k] = _stage[line][k];
			_stage[line][k] = false;       //��յ�ǰ��

		}
		line--; //�Ӹ��еĵ���һ�м����������ݺͷ���
	}
	DrawFrame();//���»�����Ϸ��
}

bool Frame::JudgeMove( Block & block, int a_block, short x, short y,int fun)
{
	Pos pos = block.Get_pos();
	pos.x += x;
	pos.y += y;
	bool move_ok = true;
	if (0 == fun)//�ж��Ƿ��з����غϣ������ж��Ƿ���Լ����ƶ�
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
	else//�жϳ��߽����Ƿ��з����غϣ����ڴ���߽緽�����
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
			_highline = pos.y + i;//�����з���������(�������Ͽ�)
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
			cout << "׳ʿ�Ǽ���˫";
			SetConsor(WINDOW_WIDTH + 3, LENGTH / 2 + 2);
			cout << "�����´���:   \b\b\b";
			ShowConsor();
			cin >> name;
			HideConsor();
			_name.push_back(name);
			_score.push_back(score);
			int temp_score;
			string temp_name;
			end = _score.size();
			for (int i = 0; i < end - 1; ++i)//��������
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

