#include<string>
void print_table(const std::string &str, int length);//��������
void print_table(int sum, int length);               //��ӡһ�����ʹ���ݾ���
void print_book(const std::string book_name, const std::string autor_name, int number);
//��ӡ�鼮��Ϣ
std::string in_password();//�������벢����*
char enter_judge(int end_pos, void(*display)(int), int &beg_pos);//�����ж�
void display_main_menu(int pos = 1);  //��ӡ���˵�
void display_admin_menu(int pos = 1); //��ӡ����Ա�˵�
void display_user_menu(int pos = 1);  //��ӡ�û��˵�(ѧ��||��ʦ)
void display_littlemenu1(int pos = 1);//��ӡ����Ա�ֲ˵�(�鼮�����˵�)
void display_littlemenu2(int pos = 1);//��ӡ����Ա�ֲ˵�(�û������˵�)
void display_choise_menu(int pos = 1);//��ӡ�鼮���ҷ�ʽ�˵�
void display_change_menu(int pos = 1);//��ӡ�ı��鼮��Ϣʱ����Ŀ�˵�