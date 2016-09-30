#include<string>
void print_table(const std::string &str, int length);//函数重载
void print_table(int sum, int length);               //打印一个表格，使数据居中
void print_book(const std::string book_name, const std::string autor_name, int number);
//打印书籍信息
std::string in_password();//输入密码并回显*
char enter_judge(int end_pos, void(*display)(int), int &beg_pos);//输入判断
void display_main_menu(int pos = 1);  //打印主菜单
void display_admin_menu(int pos = 1); //打印管理员菜单
void display_user_menu(int pos = 1);  //打印用户菜单(学生||老师)
void display_littlemenu1(int pos = 1);//打印管理员分菜单(书籍操作菜单)
void display_littlemenu2(int pos = 1);//打印管理员分菜单(用户操作菜单)
void display_choise_menu(int pos = 1);//打印书籍查找方式菜单
void display_change_menu(int pos = 1);//打印改变书籍信息时的项目菜单