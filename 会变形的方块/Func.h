#define LENGTH 22//0、1->20、21
#define WIDTH  12//0、1->10、11
#define BLOCK_WIDTH 4 //
#define BLOCK_LENGTH 0//方块距离游戏区域的距离，从(25,1)开始
#define WINDOW_WIDTH 23//
#define WINDOW_LENGTH 1//游戏区域距窗口边缘的距离，从(0,0)开始
void SetConsor(short x,short y);//设置光标位置
void HideConsor();              //隐藏光标
void ShowConsor();              //显示光标
void change_block(int x,int &rand_block);//方块变形
void drew_interface(const int mode,int color_index);//绘制游戏边界信息
void display_main_menu();
void display_mode_menu();//绘制游戏模式选单
void replay_main_menu(int last_pos, int new_pos);//选项卡移动
void replay_mode_menu(int last_pos, int new_pos);
char enter_judge(int &beg_pos, int end_pos,void (*replay)(int,int));//返回选择的函数
