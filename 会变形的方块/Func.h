#define LENGTH 22//0��1->20��21
#define WIDTH  12//0��1->10��11
#define BLOCK_WIDTH 4 //
#define BLOCK_LENGTH 0//���������Ϸ����ľ��룬��(25,1)��ʼ
#define WINDOW_WIDTH 23//
#define WINDOW_LENGTH 1//��Ϸ����ര�ڱ�Ե�ľ��룬��(0,0)��ʼ
void SetConsor(short x,short y);//���ù��λ��
void HideConsor();              //���ع��
void ShowConsor();              //��ʾ���
void change_block(int x,int &rand_block);//�������
void drew_interface(const int mode,int color_index);//������Ϸ�߽���Ϣ
void display_main_menu();
void display_mode_menu();//������Ϸģʽѡ��
void replay_main_menu(int last_pos, int new_pos);//ѡ��ƶ�
void replay_mode_menu(int last_pos, int new_pos);
char enter_judge(int &beg_pos, int end_pos,void (*replay)(int,int));//����ѡ��ĺ���
