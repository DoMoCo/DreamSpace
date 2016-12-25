//一个方块占两个字符位，当方块位置改变1，光标位置改变2
#include"Block.h"
#include"Frame.h"
#include"Func.h"
#include<iostream>
using std::cout;
using std::endl;

Block::Block()
{
	_pos.x = BLOCK_WIDTH;
	_pos.y = BLOCK_LENGTH;
	_true_pos.x = _pos.x*2 + WINDOW_WIDTH;
	_true_pos.y = _pos.y + WINDOW_LENGTH;
}

void Block::Drew_override_Block(Frame &frame,int ix,short x,short y)//-1->覆盖之前的方块;else->绘制方块
{
	short i = 0, j = 0, end_i = 4, end_j = 4, temp_j,temp_x,temp_y;
	if (x == -1 && y == -1)
	{
		if (_pos.x < 1)
			j = 1 - _pos.x;
		else if (_pos.x > 6)
			end_j = 11 - _pos.x;
		if (_pos.y < 1)
			i = 1 - _pos.y;
		else if (_pos.y > 17)
			end_i = 21 - _pos.y;
		temp_x = _true_pos.x;
		temp_y = _true_pos.y;
	}
	else
	{
		temp_x = x;
		temp_y = y;
	}
	if (temp_x < WINDOW_WIDTH + 2)
		temp_x = WINDOW_WIDTH + 2;
	if (temp_y < WINDOW_LENGTH + 1)
		temp_y = WINDOW_LENGTH + 1;
  	SetConsor(temp_x, temp_y);
	for (;i< end_i; ++i)
	{
		temp_j = j;
		for (; temp_j < end_j; ++temp_j)
		{
			if (-1 == ix)
			{
				if(frame.Get_info(_pos.y + i, _pos.x + temp_j))
					cout << "■";
				else
					cout << "  ";
			}
			else
			{
				if (_block[ix][i][temp_j] ||
					frame.Get_info(_pos.y + i, _pos.x + temp_j))
					cout << "■";
				else
					cout << "  ";
			} 
		}
		temp_y++;
		SetConsor(temp_x, temp_y);
	}
}

void Block::Change_pos(int x, int y)
{	
	if (-1 == x && -1 == y)
	{
		_pos.x = BLOCK_WIDTH;
		_pos.y = BLOCK_LENGTH;
		_true_pos.x = _pos.x*2 + WINDOW_WIDTH;
		_true_pos.y = _pos.y + WINDOW_LENGTH;
	}
	else
	{
		_pos.x += x;
		_pos.y += y;
		_true_pos.x += 2 * x;
		_true_pos.y += y;
	}
}

