#include<vector>
#include<string>
#define LENGTH 22//数组从1开始
#define WIDTH  12//数组从0开始
#define WINDOW_WIDTH 23//
#define WINDOW_LENGTH 1//游戏区域距窗口边缘的距离，从(0,0)开始
using std::vector;
using std::string;

class Block;//防止头文件重复引用的解决之法

class Frame {
public:
	Frame();                      //构造函数
	void frame_initial();         //游戏区数据初始化
	void DrawFrame();             //绘制游戏区域
	void Drew_game_over();        //绘制游戏结束的画面
	bool Get_info(int x, int y);  //获得该处的信息(是否有方块)
	void Change_info(int x, int y)//改变该坐标的信息
	{ _stage[x][y] = true;}
	int Calculate_score(Block &block);           //计算分数
	void block_down(vector<int> &full_lines);   //消行与方块下移
	bool JudgeMove( Block & block, int a_block, short x, short y,int fun=0);
	                                             //判断方块移动后是否重合
	void save_frame( Block & block, int a_block);//保存游戏区域数据，存储是否有方块
	void save_score(int score);
	void display_score();
	void save_score_data();//把游戏排名保存成文本
private:
	bool _stage[LENGTH][WIDTH];//游戏区域为20*10,左右和下分别加一行，用于判断方块是否可以移动
	int _highline;//记录有方块的最高行
	vector<string>_name;//玩家名字
	vector<int> _score;//玩家分数
};

