struct Pos {//记录方块位置
	short x;
	short y;
};
class Frame;

class Block {
public:
	Block();
	void Drew_override_Block(Frame &frame,int ix=-1,short x=-1,short y=-1);//画出方块;
	bool Get_Block(int a_block, int x, int y) { return _block[a_block][x][y]; }
	Pos Get_pos() { return _pos; }//获得光标位置
	void Change_pos(int x, int y);//改变光标位置

private:
	bool _block[20][4][4] = {
		{//0->田型
			{ false,false,false,false },
		    { false,true, true, false },
			{ false,true, true, false },
			{ false,false,false,false }
		},
		{//1->┃型
			{ false,true,false,false },
			{ false,true,false,false },
			{ false,true,false,false },
			{ false,true,false,false }
		},
		{//2->━型
			{ false,false,false,false },
			{ true, true, true, true  },
			{ false,false,false,false },
			{ false,false,false,false }
		},
		{//3->?
			{ false,true, false,false },
			{ false,true, true, false },
			{ false,false,true, false },
			{ false,false,false,false }
		},
		{//4
			{ false,false,false,false },
			{ false,true, true, false },
			{ true, true, false,false },
			{ false,false,false,false }
		},
		{//5->?
			{ false,false,true, false },
			{ false,true, true, false },
			{ false,true, false,false },
			{ false,false,false,false }
		},
		{//6
			{ false,false,false,false },
			{ true, true, false,false },
			{ false,true, true, false },
			{ false,false,false,false }
		},
		{//7->┻型
			{ false,true, false,false },
			{ true, true, true, false },
			{ false,false,false,false },
			{ false,false,false,false }
		},
		{//8
			{ false,true, false,false },
			{ false,true, true, false },
			{ false,true, false,false },
			{ false,false,false,false }
		},
		{//9
			{ false,false,false,false },
			{ true, true, true, false },
			{ false,true, false,false },
			{ false,false,false,false }
		},
		{//10
			{ false,true, false,false },
			{ true, true, false,false },
			{ false,true, false,false },
			{ false,false,false,false }
		},
		{//11->└型
			{ false,true, false,false },
			{ false,true, false,false },
			{ false,true, true, false },
			{ false,false,false,false }
		},
		{//12
			{ false,false,false,false },
			{ false,true, true, true  },
			{ false,true, false,false },
			{ false,false,false,false }
		},
		{//13
			{ false,false,false,false },
			{ false,true, true, false },
			{ false,false,true, false },
			{ false,false,true, false }
		},
		{//14
			{ false,false,false,false },
			{ false,false,true, false },
			{ true, true, true, false },
			{ false,false,false,false }
		},
		{//15->┘
			{ false,false,true, false },
			{ false,false,true, false },
			{ false,true, true, false },
			{ false,false,false,false }
		},
		{//16
			{ false,false,false,false },
			{ false,true, false,false },
			{ false,true, true, true },
			{ false,false,false,false }
		},
		{//17
			{ false,false,false,false },
			{ false,true, true, false },
			{ false,true, false,false },
			{ false,true, false,false }
		},
		{//18
			{ false,false,false,false },
			{ true, true, true, false },
			{ false,false,true, false },
			{ false,false,false,false }
		}
	};
	Pos _pos;
	Pos _true_pos;
};
