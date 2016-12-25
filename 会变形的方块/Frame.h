#include<vector>
#include<string>
#define LENGTH 22//�����1��ʼ
#define WIDTH  12//�����0��ʼ
#define WINDOW_WIDTH 23//
#define WINDOW_LENGTH 1//��Ϸ����ര�ڱ�Ե�ľ��룬��(0,0)��ʼ
using std::vector;
using std::string;

class Block;//��ֹͷ�ļ��ظ����õĽ��֮��

class Frame {
public:
	Frame();                      //���캯��
	void frame_initial();         //��Ϸ�����ݳ�ʼ��
	void DrawFrame();             //������Ϸ����
	void Drew_game_over();        //������Ϸ�����Ļ���
	bool Get_info(int x, int y);  //��øô�����Ϣ(�Ƿ��з���)
	void Change_info(int x, int y)//�ı���������Ϣ
	{ _stage[x][y] = true;}
	int Calculate_score(Block &block);           //�������
	void block_down(vector<int> &full_lines);   //�����뷽������
	bool JudgeMove( Block & block, int a_block, short x, short y,int fun=0);
	                                             //�жϷ����ƶ����Ƿ��غ�
	void save_frame( Block & block, int a_block);//������Ϸ�������ݣ��洢�Ƿ��з���
	void save_score(int score);
	void display_score();
	void save_score_data();//����Ϸ����������ı�
private:
	bool _stage[LENGTH][WIDTH];//��Ϸ����Ϊ20*10,���Һ��·ֱ��һ�У������жϷ����Ƿ�����ƶ�
	int _highline;//��¼�з���������
	vector<string>_name;//�������
	vector<int> _score;//��ҷ���
};

