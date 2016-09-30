#include<iostream>
#include"User.h"
#include"func.h"
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#undef max        //取消windows.h对max的宏定义，window.h和limits都对max做出了定义
#include<limits>  //这里会出现重复定义的错误
using namespace std;
#define space "\t\t\t\t\t\t"//调整输出位置

void borrow_book(User &user, LibMat &libmat);//借书
void return_book(User &user, LibMat &libmat);//还书
void addfile();//若文件不存在，添加必要文件
void display_start();//打印使用说明
void admin_in(LibMat &libmat);//管理员登入&&操作
void user_in(LibMat &libmat, bool user);//学生||老师登入
void user_func(LibMat &libmat, User &user, int pos);//学生||老师操作
void feedback();//意见反馈

void borrow_book(User &user,LibMat &libmat)
{
	bool borrow_it = true;//记录是否借书
	bool is_in = false;
	cout << space << "请输入你要借的书名:";
	string book_name;
	cin >> book_name;
	is_in = user.is_borrow(book_name);
	if (is_in)
		cout <<space << "你已经借了这本书！\n";
	else
	{
		bool find_it = libmat.find_book(book_name);
		if (find_it)
		{
			string autor_name = libmat.b_find_a(book_name);
			int number = libmat.num_of_book(book_name);
			print_book(book_name, autor_name, number);//打印书籍信息
			cout << space << "是否借阅?(Y/N):";
			char ch;
			cin >> ch;
			if (ch == 'n' || ch == 'N')
				borrow_it = false;
			if (borrow_it)
			{
				user.borrow_book(book_name);//借书
				libmat.borrow_book(book_name);//相关书籍的馆藏量减少
				cout << space << "借阅成功！" << endl;
			}
		}
		else
			cout << space << "Sorry," << book_name << "is unavailable!" 
			     << endl;
	} 
}

void return_book(User &user,LibMat &libmat)
{
	bool is_in;//记录这本书是否已借
	string book_name;
	do
	{
		cout << space << "请输入你要归还的书名:";
		cin >> book_name;
		is_in = user.is_borrow(book_name);
		if (!is_in)
			cout << space << "你没有借这本书！\n";
	} while (!is_in);
	user.return_book(book_name);
	libmat.return_book(book_name);
	cout << space << "归还成功!" << endl;
}

void addfile()
{
	ifstream infile("admin_password.dat");
	if (!infile)
	{
		ofstream addfile("admin_password.dat");
		addfile << "000000";
		addfile.close();
	}
	infile.close();
	ofstream addfile("book_resource.txt",ios_base::app);
	addfile.close();
	addfile.open("student_data.dat", ios_base::app);
	addfile.close();
	addfile.open("student_password.dat", ios_base::app);
	addfile.close();
	addfile.open("teacher_data.dat", ios_base::app);
	addfile.close();
	addfile.open("teacher_password.dat", ios_base::app);
	addfile.close();
}

void display_start()
{
	cout << "\n\n\t\t\t\t\t\t\t" << "    Power by DMC\n"
		 << "\t\t\t\t\t\t\t" << "All rights reserved\n";
	cout << space << " ┏━━━━━━━━━━━━━━\n"
		 << space << " ┃\n"      
		 << space << " ┃       功能说明:\n"
		 << space << " ┃ 打     1、你可以通过↑、↓\n"
		 << space << " ┃ 开        w、s来移动选择框\n"
		 << space << " ┃ 全     2、按Enter、Space、\n"
		 << space << " ┃ 屏        →或d确定功能\n"
	 	 << space << " ┃ 以     3、按Esc、a或←回退\n"
		 << space << " ┃ 获     4、当然你也可以通过\n"
		 << space << " ┃ 得        功能序号+Enter来\n"
		 << space << " ┃ 更        选择功能\n"
		 << space << " ┃ 佳     5、所有用户默认密码\n"
		 << space << " ┃ 的        为000000\n"
		 << space << " ┃ 体     6、键入书名时请带上\n"
		 << space << " ┃ 验        书名号\n"
		 << space << " ┃\n"
	     << space << " ┃\n";
	cout << space << " 请按任意键继续...";
	_getch();
}

void admin_in(LibMat &libmat)
{
	Admin admin;
	vector<vector<string> >::iterator book;//用于处理find_student、find_teacher函数
	bool student = false;                  //记录学生数据是否修改，修改则保存
	bool teacher = false;				   //记录老师数据是否修改
	bool save_password = false;			   //记录密码是否修改
	cout << space << "请输入管理员的密码(6位):";
	string password;
	password = in_password();//输入密码
	while (password.empty())
	{
		cout<<'\n' << space << "输 入 有 误，请重新输入:";
		password = in_password();
	}
	bool check_success = admin.check_in(password);
	if (check_success)
	{
		cout<<'\n' << space << "登入成功！请稍后...";
		Sleep(1000);          //等待1秒
		bool end_it = true;   //判断是否结束操作
		bool back = false;    //判断操作是否回到管理员的初始界面(有分菜单)
		display_admin_menu(); //打印管理员操作界面
		cout << space;
		int pos_1 = 1, pos_2 = 1, pos_3 = 1;//记录上次选择框的位置，初始为1
		char ch = ' ';        //记录选择的功能
		do
		{
			ch = enter_judge(9,display_admin_menu,pos_1);
			switch (ch)
			{
			case'1': admin.display_book(libmat); break;
			case'2': admin.display_student(); break;
			case'3': admin.display_teacher(); break;
			case'4': display_littlemenu1();
				     cout << space;
					 pos_2 = 1;
					 do
					 {
						 back = false;
						 ch = enter_judge(5, display_littlemenu1,pos_2);
						 switch (ch)
						 {
						 case'1': admin.find_book(libmat,true); break;
						 case'2': admin.add_book(libmat);  break;
						 case'3': admin.change_book(libmat); break;
						 case'4': admin.remove_book(libmat); break;
						 case'5': back = true; display_admin_menu(pos_1); break;
						 default: cout << space << "输入有误,键入回车以继续！" << endl; 
							      cin.clear();
								  cin.ignore(numeric_limits<streamsize>::max(), '\n');
						 }//清除输入缓冲区(当前行)
						 if (!back)
							 cout << space << "请继续操作:";
					 } while (!back);
					 break;
			case'5': display_littlemenu2();
					 cout << space;
					 pos_3 = 1;
					 do
					 {
						 back = false;
						 ch = enter_judge(7, display_littlemenu2,pos_3);
						 switch (ch)
						 {
						 case'1': admin.find_student(book); break;
						 case'2': admin.add_student(); student = true; break;
						 case'3': admin.remove_student(); student = true; break;
						 case'4': admin.find_teacher(book); break;
						 case'5': admin.add_teacher(); teacher = true; break;
						 case'6': admin.remove_teacher(); teacher = true; break;
						 case'7': back = true; display_admin_menu(pos_1); break;
						 default: cout << space << "输入有误，键入回车以继续！" << endl; 
						 cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
						 }
						 if (!back)
							 cout << space << "请继续操作:";
					 } while (!back);
					 break;
			case'6': admin.change_password(); save_password = true; break;
			case'7': end_it = !admin.delete_all_data(libmat); 
				     student = true;
				     teacher = true;
					 save_password = true; break;
			case'8': system("cls"); display_admin_menu(); pos_1 = 1; break;
			case'9': end_it = false; break;
			default: cout << space << "输入有误，键入回车以继续！" << endl; cin.clear();
				     cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}	     
			if (end_it)
				cout << space << "请继续操作:";
		} while (end_it);
		admin.check_out(student,teacher,save_password);//保存数据
		system("cls");//刷新
		display_main_menu(1);//打印主菜单，选择框位置为1
	}
	else
		cout<< " 密码错误，回天乏术!!!" << endl;
}

void user_in(LibMat &libmat, bool user)
{
	if (user)
	{
		cout << space << "请 输 入 你 的 学 号:";
		string user_id;
		cin >> user_id;
		Student student(user_id);
		user_func(libmat, student, 2);
	}
	else
	{
		cout << space << "请 输 入 你 的 工 号:";
		string user_id;
		cin >> user_id;
		Teacher teacher(user_id);
		user_func(libmat, teacher, 3);
	}
}

void user_func(LibMat &libmat, User &user,int pos)
{                                //pos记录主菜单选择框位置
	bool save_me = true;         //记录是否销毁自己的数据
	cout << space << "请输入你的密码 (6位):";
	string password;
	password = in_password();
	while (password.empty())
	{
		cout <<'\n'<< space << "输入有误，请重新输入:";
		password = in_password();
	}
	bool check_success = user.check_in(password);
	if (check_success)
	{
		cout <<'\n'<< space << "登入成功！请稍后..." ;
		Sleep(1000);
		bool end_it = true;
		display_user_menu();
		cout << space;
		int pos_1 = 1;//记录选择框位置
		do
		{
			char ch=' ';
			ch = enter_judge(8,display_user_menu,pos_1);
			switch (ch)
			{
			case'1':user.display_borrow(libmat); break;
			case'2':user.display_data(); break;
			case'3':borrow_book(user, libmat); break;
			case'4':return_book(user, libmat); break;
			case'5':user.change_password(); break;
			case'6':save_me = user.kill_me(); end_it = save_me; break;
			case'7':system("cls"); display_user_menu(); pos_1 = 1; break;
			case'8':end_it = false; break;
			default:cout << space << "输入有误，键入回车以继续！" << endl; cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}	    //清除输入缓存区的内容     
			if (end_it)
				cout << space << "请继续操作:";
		} while (end_it);
		user.check_out(save_me,true);//保存数据
		system("cls");
		display_main_menu(pos);//打印主菜单，选择框位置为2或3
	}
	else if ((user.user_name()).empty())
		cout << " 账号不存在，快拨打我们的客服热线注册账号吧！\n";
	else
		cout << " 密码错误！\n"
	         << space << "请联系管理员,或访问www.tobethebest.cn修改你的密码。";
}

void feedback()//功能尚待完善->中文不好处理
{
	bool good_back = true;//判断有没脏话
	cout << space << "请输入你的意见:";
	string feed;
	cin >> feed;
	stringstream text(feed);
	char ch_temp[2];
	while (text >> ch_temp[0]&&text>>ch_temp[1])
	{
		if ((ch_temp[0]=='s'&&ch_temp[1]=='b')||(ch_temp[0]=='S'&&ch_temp[1]=='B'))
			good_back = false;
	}
	if (good_back)
		cout << space << "我们会及时处理你的意见，谢谢你的反馈！" << endl;
	else
		cout << space << "请使用文明用语！" << endl;
	cout << space << "按任意键继续...";
	_getch();
	display_main_menu(4);//打印主菜单，选择框位置为4
}


int main()
{
	addfile();
	display_start();
	LibMat libmat;
	display_main_menu();
	cout << space;
	bool end_it = true;
	int pos=1;
	do
	{ 
		char ch = ' ';
		ch = enter_judge(5,display_main_menu,pos);
		switch (ch)
		{
		case'1':admin_in(libmat); break;
		case'2':user_in(libmat,true); break;
		case'3':user_in(libmat,false); break;
		case'4':feedback(); break;
		case'5':end_it = false; break;
		default:cout << space << "输入有误，键入回车以继续！" << endl;

			cin.clear();cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}	    //清除输入缓存区的内容,终止字符为'\n'，输入中文字符会出错，无解   
		if (end_it)
			cout << space << "请继续操作:";
	} while (end_it);
	libmat.check_out();//保存图书数据
	cout << space<<"欢迎再次访问！";
	system("pause");
	return 0;
}

