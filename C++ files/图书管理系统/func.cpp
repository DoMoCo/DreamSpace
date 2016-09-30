#include<iostream>
#include<string>
#include<iomanip>
#include<conio.h>
#define space "\t\t\t\t\t\t"
using namespace std;

void print_table(const string &str, int length)
{
	int len = (length - str.size()) / 2;
	for (int ix = 0; ix < len; ++ix)
		cout << ' ';
	cout << str;
	len = length - str.size() - len;
	for (int ix = 0; ix < len; ++ix)
		cout << ' ';
	cout << "│";
}

void print_table(int sum, int length)
{
	int space_table=0;
	int temp = sum;
	while (temp >= 10)//取得数字位数
	{
		temp /= 10;
		space_table++;
	}
	space_table++;
	int len = (length-space_table )/ 2;//折半处理，使在表格数字居中
	for (int ix = 0; ix < len; ++ix)
		cout << ' ';
	cout << sum;
	len = length - space_table - len;
	for (int ix = 0; ix < len; ++ix)
		cout << ' ';
	cout << "│";
}

void print_book(const string book_name,const string autor_name,int number)
{
	cout << space << "Find it!" << "\n"
		<< space << "┌─────────────┬──────────┬────┐\n"
		<< space << "│           书名           │        作者        │ 馆藏量 │\n"
		<< space << "├─────────────┼──────────┼────┤\n"
		<< space << "│";
	print_table(book_name, 26);
	print_table(autor_name, 20);
	print_table(number, 8);
	cout <<"\n"
		<< space <<"└─────────────┴──────────┴────┘\n";
}

string in_password()
{
	int i=0;
	char ch;
	char passwd[7] = {' '};
	while ((ch = _getch()) != '\r'&&i<7)
	{
		if (ch != 8)//不是回撤就录入
		{
			passwd[i] = ch;
			putchar('*');//并且输出*号
			i++;
		}
		else
		{
			putchar('\b'); //这里是删除一个，我们通过输出回撤符 /b，回撤一格，
			putchar(' '); //再显示空格符把刚才的*给盖住，
			putchar('\b');//然后再回撤一格等待录入。
			i--;
		}
	}
	if(i==6)//输入正确，添加字符串结束符
		passwd[i] = '\0';
	else
		return "";
	char *cp = passwd;
	string password(passwd);
	return password;
}

char enter_judge(int end_pos, void(*display)(int), int &beg_pos)//返回选择的函数
{
	bool go_for_it = true;//用于跳出外层循环，当然这里也适合用goto
	char func = ' ';
	char ch_1, ch_2, ch_temp;
	char end_it;          //标记结束或跳出程序
	if (end_pos < 10)
		end_it = end_pos + 48;
	else
		end_it = end_pos + 87;
	while (go_for_it)
	{
		ch_1 = _getch();
		switch (ch_1)
		{
		case -32:
			ch_2 = _getch();
			switch (ch_2)
			{
			case 72:  if (beg_pos > 1)         //方向上键
						  beg_pos--;
					  else
						  beg_pos = end_pos;
					  break;
			case 80:  if (beg_pos<end_pos)
						  beg_pos++;
					  else
						  beg_pos = 1;
					  break;        //方向下键
			case 75:  func = end_it; go_for_it = false;
				      break;                     //方向左键
			case 77:  if (beg_pos < 10)        //方向右键
						  func = beg_pos + 48;//0->'1'、'2'、'3'...
					  else
						  func = beg_pos + 87;//0->'a'、'b'、'c'...
				      go_for_it = false;
				      break;
			}
			break;
		case 'a':
		case 'A':func = end_it; go_for_it = false; break;
		case 'd':
		case 'D':if (beg_pos < 10)
				     func = beg_pos + 48;
				 else
					 func = beg_pos + 87;
				go_for_it = false;
			break;
		case 'w':
		case 'W':if (beg_pos > 1)
				     beg_pos--;
				 else
					 beg_pos = end_pos;
			break;
		case 's':
		case 'S':if (beg_pos < end_pos)
					 beg_pos++;
				 else
					 beg_pos = 1;
			     break;
		case'\r':if (beg_pos < 10)
			func = beg_pos + 48;
				 else
					 func = beg_pos + 87;
			go_for_it = false;
			break;
		case 0x1B:func = end_it; go_for_it = false; break;//Esc跳出当前选单
		case'1':
		case'2':
		case'3':
		case'4':
		case'5':
		case'6':
		case'7':
		case'8':
		case'9':cout << ch_1;
				ch_temp = _getch();
				if (ch_temp == '\r')
					func = ch_1;
				else
					func = ch_1 + ch_temp;//10->'a','a'=1+0+96
			    cout << ch_temp;
			    go_for_it = false;
				break;
		default: cout << ch_1; go_for_it = false;
		}
		if (go_for_it)
		{
			(*display)(beg_pos);
			cout << space << "请继续操作:";
		}	
	}
	cout << endl;
	return func;
}

void display_main_menu(int pos )
{
	system("cls");
	cout     << "\n\t\t\t\t\t" <<"        ┏───────────┓\n"
		     << space << "│┌┄┄┄┄┄┄┄┄┄┐│\n"
		     << space << "│┆      主菜单      ┆│\n";
	if (pos == 1)
		cout << space << "│┢━━━━━━━━━┪│\n"
			 << space << "│┃  1、管理员登入   ┃│\n"
			 << space << "│┡━━━━━━━━━┩│\n"
			 << space << "│┆  2、学生登入     ┆│\n";
	else
		cout << space << "│├┄┄┄┄┄┄┄┄┄┤│\n"
			 << space << "│┆  1、管理员登入   ┆│\n";
	if (pos == 2)
		cout << space << "│┢━━━━━━━━━┪│\n"
			 << space << "│┃  2、学生登入     ┃│\n"
			 << space << "│┡━━━━━━━━━┩│\n"
			 << space << "│┆  3、教师登入     ┆│\n";
	else if (pos != 1)
		cout << space << "│├┄┄┄┄┄┄┄┄┄┤│\n"
			 << space << "│┆  2、学生登入     ┆│\n";
	if (pos == 3)
		cout << space << "│┢━━━━━━━━━┪│\n"
			 << space << "│┃  3、教师登入     ┃│\n"
			 << space << "│┡━━━━━━━━━┩│\n"
			 << space << "│┆  4、意见反馈     ┆│\n";
	else if (pos != 2)
		cout << space << "│├┄┄┄┄┄┄┄┄┄┤│\n"
			 << space << "│┆  3、教师登入     ┆│\n";
	if (pos == 4)
		cout << space << "│┢━━━━━━━━━┪│\n"
			 << space << "│┃  4、意见反馈     ┃│\n"
			 << space << "│┡━━━━━━━━━┩│\n"
			 << space << "│┆  5、退出         ┆│\n";
	else if (pos != 3)
		cout << space << "│├┄┄┄┄┄┄┄┄┄┤│\n"
			 << space << "│┆  4、意见反馈     ┆│\n";
	if (pos == 5)
		cout << space << "│┢━━━━━━━━━┪│\n"
			 << space << "│┃  5、退出         ┃│\n"
			 << space << "│┗━━━━━━━━━┛│";
	else if (pos != 4)
		cout << space << "│├┄┄┄┄┄┄┄┄┄┤│\n"
			 << space << "│┆  5、退出         ┆│\n"
			 << space << "│└┄┄┄┄┄┄┄┄┄┘│";
	else
		cout << space << "│└┄┄┄┄┄┄┄┄┄┘│";
	cout << "\n\t\t\t\t\t" << "        ┗───────────┛\n";
}

void display_admin_menu(int pos )
{
	system("cls");
	cout     << space << "┌┄┄┄┄┄┄┄┄┄┐\n"
			 << space << "┆   老子是管理员   ┆\n";
	if (pos == 1)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 1、 查看书籍信息 ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 2、 查看学生用户 ┆\n";
	else
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 1、 查看书籍信息 ┆\n";
	if (pos == 2)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 2、 查看学生用户 ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 3、 查看教师用户 ┆\n";
	else if (pos != 1)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 2、 查看学生用户 ┆\n";
	if (pos == 3)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 3、 查看教师用户 ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 4、 书籍操作     ┆\n";
	else if (pos != 2)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 3、 查看教师用户 ┆\n";
	if (pos == 4)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 4、 书籍操作     ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 5、 用户操作     ┆\n";
	else if (pos != 3)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 4、 书籍操作     ┆\n";
	if (pos == 5)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 5、 用户操作     ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 6、 修改密码     ┆\n";
	else if (pos != 4)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 5、 用户操作     ┆\n";
	if (pos == 6)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 6、 修改密码     ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 7、 创世纪       ┆\n";
	else if (pos != 5)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 6、 修改密码     ┆\n";
	if (pos == 7)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 7、 创世纪       ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 8、 刷新         ┆\n";
	else if (pos != 6)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 7、 创世纪       ┆\n";
	if (pos == 8)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 8、 刷新         ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 9、 回到主菜单   ┆\n";
	else if (pos != 7)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 8、 刷新         ┆\n";
	if (pos == 9)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 9、 回到主菜单   ┃\n"
			 << space << "┗━━━━━━━━━┛\n";
	else if (pos != 8)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 9、 回到主菜单   ┆\n"
			 << space << "└┄┄┄┄┄┄┄┄┄┘\n";
	else
		cout << space << "└┄┄┄┄┄┄┄┄┄┘\n";
}

void display_littlemenu1(int pos )
{
	system("cls");
	if (pos == 1)
		cout << space << "┏━━━━━━━━━┓\n"
			 << space << "┃ 1、 查找书籍     ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 2、 添加书籍     ┆\n";
	else
		cout << space << "┌┄┄┄┄┄┄┄┄┄┐\n"
			 << space << "┆ 1、 查找书籍     ┆\n";
	if (pos == 2)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 2、 添加书籍     ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 3、 修改书籍信息 ┆\n";
	else if (pos != 1)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 2、 添加书籍     ┆\n";
	if (pos == 3)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 3、 修改书籍信息 ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 4、 删除书籍     ┆\n";
	else if (pos != 2)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 3、 修改书籍信息 ┆\n";
	if (pos == 4)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 4、 删除书籍     ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 5、 回到上一级   ┆\n";
	else if (pos != 3)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 4、 删除书籍     ┆\n";
	if (pos == 5)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 5、 回到上一级   ┃\n"
			 << space << "┗━━━━━━━━━┛\n";
	else if (pos != 4)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 5、 回到上一级   ┆\n"
			 << space << "└┄┄┄┄┄┄┄┄┄┘\n";
	else
		cout << space << "└┄┄┄┄┄┄┄┄┄┘\n";
}

void display_littlemenu2(int pos )
{
	system("cls");
	if (pos == 1)
		cout << space << "┏━━━━━━━━━┓\n"
			 << space << "┃ 1、 查找学生用户 ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 2、 添加学生用户 ┆\n";
	else
		cout << space << "┌┄┄┄┄┄┄┄┄┄┐\n"
			 << space << "┆ 1、 查找学生用户 ┆\n";
	if (pos == 2)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 2、 添加学生用户 ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 3、 移除学生用户 ┆\n";
	else if (pos != 1)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 2、 添加学生用户 ┆\n";
	if (pos == 3)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 3、 移除学生用户 ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 4、 查找教师用户 ┆\n";
	else if (pos != 2)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 3、 移除学生用户 ┆\n";
	if (pos == 4)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 4、 查找教师用户 ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 5、 添加教师用户 ┆\n";
	else if (pos != 3)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 4、 查找教师用户 ┆\n";
	if (pos == 5)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 5、 添加教师用户 ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 6、 移除教师用户 ┆\n";
	else if (pos != 4)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 5、 添加教师用户 ┆\n";
	if (pos == 6)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 6、 移除教师用户 ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 7、 回到上一级   ┆\n";
	else if (pos != 5)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 6、 移除教师用户 ┆\n";
	if (pos == 7)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 7、 回到上一级   ┃\n"
			 << space << "┗━━━━━━━━━┛\n";
	else if (pos != 6)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 7、 回到上一级   ┆\n"
			 << space << "└┄┄┄┄┄┄┄┄┄┘\n";
	else
		cout << space << "└┄┄┄┄┄┄┄┄┄┘\n";
}

void display_user_menu(int pos )
{
	system("cls");
	cout	 << space << "┌┄┄┄┄┄┄┄┄┄┐\n"
			 << space << "┆    尊贵的用户    ┆\n";
	if (pos == 1)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 1、 查看借阅信息 ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 2、 查看我的信息 ┆\n";
	else
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 1、 查看借阅信息 ┆\n";
	if (pos == 2)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 2、 查看我的信息 ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 3、 借书         ┆\n";
	else if (pos != 1)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 2、 查看我的信息 ┆\n";
	if (pos == 3)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 3、 借书         ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 4、 还书         ┆\n";
	else if (pos != 2)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 3、 借书         ┆\n";
	if (pos == 4)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 4、 还书         ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 5、 修改登入密码 ┆\n";
	else if (pos != 3)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 4、 还书         ┆\n";
	if (pos == 5)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 5、 修改登入密码 ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 6、 老子不读书了 ┆\n";
	else if (pos != 4)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 5、 修改登入密码 ┆\n";
	if (pos == 6)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 6、 老子不读书了 ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 7、 刷新         ┆\n";
	else if (pos != 5)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 6、 老子不读书了 ┆\n";
	if (pos == 7)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 7、 刷新         ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 8、 回到主菜单   ┆\n";
	else if (pos != 6)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 7、 刷新         ┆\n";
	if (pos == 8)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 8、 回到主菜单   ┃\n"
			 << space << "┗━━━━━━━━━┛\n";
	else if (pos != 7)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 8、 回到主菜单   ┆\n"
			 << space << "└┄┄┄┄┄┄┄┄┄┘\n";
	else
		cout << space << "└┄┄┄┄┄┄┄┄┄┘\n";
}

void display_choise_menu(int pos)
{
	system("cls");
	cout	 << space << "┌┄┄┄┄┄┄┄┄┄┐\n"
			 << space << "┆  请选择查找方式  ┆\n";
	if (pos == 1)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 1、 按书名       ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 2、 按作者       ┆\n";
	else
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 1、 按书名       ┆\n";
	if (pos == 2)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 2、 按作者       ┃\n"
			 << space << "┗━━━━━━━━━┛\n";
	else if (pos != 1)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 2、 按作者       ┆\n"
			 << space << "└┄┄┄┄┄┄┄┄┄┘\n";
	else
		cout << space << "└┄┄┄┄┄┄┄┄┄┘\n";
}

void display_change_menu(int pos)
{
	system("cls");
	cout	 << space << "┌┄┄┄┄┄┄┄┄┄┐\n"
			 << space << "┆  请选择修改项目  ┆\n";
	if (pos == 1)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 1、 书名         ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 2、 作者名       ┆\n";
	else
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 1、 书名         ┆\n";
	if (pos == 2)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 2、 作者名       ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 3、 馆藏量       ┆\n";
	else if (pos != 1)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 2、 作者名       ┆\n";
	if (pos == 3)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 3、 馆藏量       ┃\n"
			 << space << "┡━━━━━━━━━┩\n"
			 << space << "┆ 4、 回到上一级   ┆\n";
	else if (pos != 2)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 3、 馆藏量       ┆\n";
	if (pos == 4)
		cout << space << "┢━━━━━━━━━┪\n"
			 << space << "┃ 4、 回到上一级   ┃\n"
			 << space << "┗━━━━━━━━━┛\n";
	else if (pos != 3)
		cout << space << "├┄┄┄┄┄┄┄┄┄┤\n"
			 << space << "┆ 4、 回到上一级   ┆\n"
			 << space << "└┄┄┄┄┄┄┄┄┄┘\n";
	else
		cout << space << "└┄┄┄┄┄┄┄┄┄┘\n";
}