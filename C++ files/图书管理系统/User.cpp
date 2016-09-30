#include"User.h"
#include"func.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<algorithm>
#include<conio.h>//使用getch();
#include<limits> 
#define space "\t\t\t\t\t\t"
using namespace std;

//class Student 
Student::Student(const string &id):User()
{
	_id=id;
	ifstream infile("student_data.dat");
	if (!infile)
		cerr << space << "Oops!Cannot open the file" << endl;
	else
	{
		string text;
		string id_temp;
		string user_name;
		string academe;
		string book_name;
		while (getline(infile, text) && (!text.empty()))
		{
			istringstream line(text);
			line >> id_temp;
			line >> user_name;
			line >> academe;
			if (id_temp == _id)
			{
				_user_name = user_name;
				_academe = academe;
				while (line >> book_name)
					_borrow_book.push_back(book_name);
				break;
			}
			_file1.push_back(text);
		}
		while (getline(infile, text) && (!text.empty()))
			_file2.push_back(text);
	}
	infile.close();
	infile.open("student_password.dat");
	if (!infile)
		cerr << space << "Oops!Cannot open the file" << endl;
	else
	{
		string text;
		string password;
		string id_temp;
		while (getline(infile, text) && (!text.empty()))
		{
			istringstream line(text);
			line >> id_temp;
			if (id_temp == _id)
			{
				line >> password;
				_password = password;
				break;
			}
			_file3.push_back(text);
		}
		while (getline(infile, text) && (!text.empty()))
			_file4.push_back(text);
	}
	infile.close();
}

bool Student::check_in(const string &password)
{
	if (password == _password)
		return true;
	else
		return false;
		
}

 void Student::return_book(std::string &book_name)
{
	vector<string>::iterator iter;
	iter = find(_borrow_book.begin(), _borrow_book.end(), book_name);
	_borrow_book.erase(iter);
}

 bool Student::kill_me()
 {
	 cout << space << "你的所有数据都将被销毁，确定要自我毁灭吗?(Y/N):";
	 char ch;
	 cin >> ch;
	 if (ch == 'Y' || ch == 'y')
	 {
		 cout << space << "再见，不再见！" << endl;
		 cout << space << "按任意键继续...";
		 _getch();
		 return false;
	 }
	 cout << space << "你从鬼门关走了一遭！" << endl;
	 return true;
 }

 void Student::display_borrow(LibMat &libmat)
 {
	 vector<string>::iterator beg = _borrow_book.begin();
	 vector<string>::iterator end_it = _borrow_book.end(); 
	 cout << space << "┌─────────────┬──────────┐\n"
		  << space << "│           书名           │        作者        │\n";
	 for (; beg != end_it; ++beg)
	 {
		 cout << space << "├─────────────┼──────────┤\n"
			  << space << "│";
		 print_table(*beg, 26);
		 string autor_name = libmat.b_find_a(*beg);
		 print_table(autor_name, 20);
		 cout << endl;
	 }
	 cout << space << "└─────────────┴──────────┘"
	      << endl;
 }

void Student::display_data()
{
	cout << space << "┌──────┬──────┬──────────┐\n"
		 << space << "│    学号    │    姓名    │        学院        │\n"
		 << space << "├──────┼──────┼──────────┤\n"
		 << space << "│";
	print_table(_id, 12);
	print_table(_user_name, 12);
	print_table(_academe, 20);
	cout << "\n"
		 << space << "└──────┴──────┴──────────┘"
		 << endl;
}

 bool Student::is_borrow(std::string book_name)
 {
	 vector<string>::iterator iter;
	 iter = find(_borrow_book.begin(), _borrow_book.end(), book_name);
	 if (iter == _borrow_book.end())
		 return false;
	 else
		 return true;
 }

 void Student::change_password()
 {
	 bool try_again;
	 do
	 {
		 try_again = false;
		 cout << space << "请输入新密码( 6位 ) :";
		 string password;
		 password = in_password();
		 while (password.empty())
		 {
			 cout<<'\n' << space << "输入有误，请重新输入:";
			 password = in_password();
		 }
		 cout<<'\n' << space << "确 认 密 码 ( 6位 ) :";
		 string password_temp;
		 password_temp=in_password();
		 while (password_temp.empty())
		 {
			 cout << '\n' << space << "输入有误，请重新输入:";
			 password_temp = in_password();
		 }
		 if (password != password_temp)
		 {
			 cout << '\n' << space << "密码不一致！请重试。\n";
			 try_again = true;
		 }
		 else
			 _password = password;
	 } while (try_again);
	 cout << '\n' << space << "修改成功，请牢记你的新密码！" << endl;
 }

void Student::check_out(bool save_me,bool book=true)
 {
	 ofstream outfile("student_data.dat");
	 if (!outfile)
		 cerr << space << "Oops!Cannot open the file" << endl;
	 else
	 {
		 vector<string>::iterator beg = _file1.begin();
		 vector<string>::iterator end_it = _file1.end();
		 for (; beg != end_it; ++beg)
			 outfile << *beg << endl;
		 if (save_me)
		 {
			 outfile << _id << ' ' << _user_name << ' ' << _academe << ' ';
			 beg = _borrow_book.begin();
			 end_it = _borrow_book.end();
			 for (; beg != end_it; ++beg)
				 outfile << *beg << ' ';
			 outfile << endl;
		 }
		 beg = _file2.begin();
		 end_it = _file2.end();
		 for (; beg != end_it; ++beg)
			 outfile << *beg << endl;
	 }
	 outfile.close();
	 outfile.open("student_password.dat");
	 if (!outfile)
		 cerr << space << "Oops!Cannot open the file" << endl;
	 else
	 {
		 vector<string>::iterator beg = _file3.begin();
		 vector<string>::iterator end_it = _file3.end();
		 for (; beg != end_it; ++beg)
			 outfile << *beg << endl;
		 if (save_me)
			 outfile << _id << ' ' << _password << endl;
		 beg = _file4.begin();
		 end_it = _file4.end();
		 for (; beg != end_it; ++beg)
			 outfile << *beg << endl;
	 }
	 outfile.close();
 }

//class Teacher
Teacher::Teacher(const string &job_num):User()
{
	_job_num=job_num;
	ifstream infile("teacher_data.dat");
	if (!infile)
		cerr << space << "Oops!Cannot open the file" << endl;
	else
	{
		string text;
		string id_temp;
		string user_name;
		string book_name;
		while (getline(infile, text) && (!text.empty()))
		{
			istringstream line(text);
			line >> id_temp;
			line >> user_name;
			if (id_temp == _job_num)
			{
				_user_name = user_name;				
				while (line >> book_name)
					_borrow_book.push_back(book_name);
				break;
			}
			_file1.push_back(text);
		}
		while (getline(infile, text) && (!text.empty()))
			_file2.push_back(text);
	}
	infile.close();
	infile.open("teacher_password.dat");
	if (!infile)
		cerr << space << "Oops!Cannot open the file" << endl;
	else
	{
		string text;
		string password;
		string id_temp;
		while (getline(infile, text) && (!text.empty()))
		{
			istringstream line(text);
			line >> id_temp;
			if (id_temp == _job_num)
			{
				line >> password;
				_password = password;
				break;
			}
			_file3.push_back(text);
		}
		while (getline(infile, text) && (!text.empty()))
			_file4.push_back(text);
	}
	infile.close();
}

bool Teacher::check_in(const string &password)
{
	if (password == _password)
		return true;
	else
		return false;

}

void Teacher::return_book(std::string &book_name)
{
	vector<string>::iterator iter;
	iter = find(_borrow_book.begin(), _borrow_book.end(), book_name);
	_borrow_book.erase(iter);
}

bool Teacher::kill_me()
{
	cout << space << "你的所有数据都将被销毁，确定要自我毁灭吗?(Y/N):";
	char ch;
	cin >> ch;
	if (ch == 'Y' || ch == 'y')
	{
		cout << space << "再见，不再见！" << endl;
		cout << space << "按任意键继续...";
		_getch();
		return false;
	}
	cout << space << "你从鬼门关走了一遭！" << endl;
	return true;
}

void Teacher::display_borrow(LibMat &libmat)
{
	vector<string>::iterator beg = _borrow_book.begin();
	vector<string>::iterator end_it = _borrow_book.end();
	cout << space << "┌─────────────┬──────────┐\n"
		 << space << "│           书名           │        作者        │\n";
	for (; beg != end_it; ++beg)
	{
		cout << space << "├─────────────┼──────────┤\n"
			 << space << "│";
		print_table(*beg, 26);
		string autor_name = libmat.b_find_a(*beg);
		print_table(autor_name, 20);
		cout << endl;
	}
	cout << space << "└─────────────┴──────────┘";
	cout << endl;
}

void Teacher::display_data()
{
	cout << space << "┌──────┬──────┐\n"
		 << space << "│    工号    │    姓名    │\n"
		 << space << "├──────┼──────┤\n"
		 << space << "│";
	print_table(_job_num, 12);
	print_table(_user_name, 12);
	cout << "\n"
		 << space << "└──────┴──────┘"
		 << endl;
}

bool Teacher::is_borrow(std::string book_name)
{
	vector<string>::iterator iter;
	iter = find(_borrow_book.begin(), _borrow_book.end(), book_name);
	if (iter == _borrow_book.end())
		return false;
	else
		return true;
}

void Teacher::change_password()
{
	bool try_again;
	do
	{
		try_again = false;
		cout << space << "请输入新密码( 6位 ) :";
		string password;
		password = in_password();
		while (password.empty())
		{
			cout << '\n' << space << "输入有误，请重新输入:";
			password = in_password();
		}
		cout << '\n' << space << "确 认 密 码 ( 6位 ) :";
		string password_temp;
		password_temp = in_password();
		while (password_temp.empty())
		{
			cout << '\n' << space << "输入有误，请重新输入:";
			password_temp = in_password();
		}
		if (password != password_temp)
		{
			cout << '\n' << space << "密码不一致！请重试。\n";
			try_again = true;
		}
		else
			_password = password;
	} while (try_again);
	cout << '\n' << space << "修改成功，请牢记你新的密码！" << endl;
}

void Teacher::check_out(bool save_me,bool book=true)
{
	ofstream outfile("teacher_data.dat");
	if (!outfile)
		cerr << space << "Oops!Cannot open the file" << endl;
	else
	{
		vector<string>::iterator beg = _file1.begin();
		vector<string>::iterator end_it = _file1.end();
		for (; beg != end_it; ++beg)
			outfile << *beg << endl;
		if (save_me)
		{
			outfile << _job_num << ' ' << _user_name << ' ';
			beg = _borrow_book.begin();
			end_it = _borrow_book.end();
			for (; beg != end_it; ++beg)
				outfile << *beg << ' ';
			outfile << endl;
		}
		beg = _file2.begin();
		end_it = _file2.end();
		for (; beg != end_it; ++beg)
			outfile << *beg << endl;
	}
	outfile.close();
	outfile.open("teacher_password.dat");
	if (!outfile)
		cerr << space << "Oops!Cannot open the file" << endl;
	else
	{
		vector<string>::iterator beg = _file3.begin();
		vector<string>::iterator end_it = _file3.end();
		for (; beg != end_it; ++beg)
			outfile << *beg << endl;
		if (save_me)
			outfile << _job_num << ' ' << _password << endl;
		beg = _file4.begin();
		end_it = _file4.end();
		for (; beg != end_it; ++beg)
			outfile << *beg << endl;
	}
	outfile.close();
}

//class Admin
Admin::Admin()
{
	//读取admin_password文件数据
	ifstream infile("admin_password.dat");
	if (!infile)
		cerr << space << "Oops!Cannot open the file" << endl;
	else
	{
		string password;
		while (infile >> password && (!password.empty()))
			_password = password;  //仅有一位管理员
	}
	infile.close();
	//读取student_data文件数据
	infile.open("student_data.dat");
	if (!infile)
		cerr << space << "Oops!Cannot open the file" << endl;
	else
	{
		string text;
		string id;
		string user_name;
		string academe;
		string book_name;
		vector<string> book_name_temp;
		while (getline(infile, text) && (!text.empty()))//判断读入是否为空
		{
			istringstream line(text);
			line >> id;
			line >> user_name;
			line >> academe;
			_student_name.push_back(user_name);
			_student_id.push_back(id);
			_student_academe.push_back(academe);
			while (line >> book_name)
				book_name_temp.push_back(book_name);
			_student_book.push_back(book_name_temp);	
		}
	}
	infile.close();
	//读取student_password文件数据
	infile.open("student_password.dat");
	if (!infile)
		cerr << space << "Oops!Cannot open the file" << endl;
	else
	{
		string text;
		string password;
		string id;
		while (getline(infile, text) && (!text.empty()))
		{
			istringstream line(text);
			line >> id;
			line >> password;
			_student_password[id] = password;
		}
	}
	infile.close();
	//读取teacher_data文件数据
    infile.open("teacher_data.dat");
	if (!infile)
		cerr << space << "Oops!Cannot open the file" << endl;
	else
	{
		string text;
		string id;
		string user_name;
		string book_name;
		vector<string> book_name_temp;
		while (getline(infile, text) && (!text.empty()))
		{
			istringstream line(text);
			line >> id;
			line >> user_name;
			_teacher_id.push_back(id);
			_teacher_name.push_back(user_name);
			while (line >> book_name)
				book_name_temp.push_back(book_name);
			_teacher_book.push_back(book_name_temp);
		}

	}
	infile.close();
	//读取teacher_password文件数据
	infile.open("teacher_password.dat");
	if (!infile)
		cerr << space << "Oops!Cannot open the file" << endl;
	else
	{
		string text;
		string password;
		string id;
		while (getline(infile, text) && (!text.empty()))
		{
			istringstream line(text);
			line >> id;
			line >> password;
			_teacher_password[id] = password;
		}
	}
	infile.close();
}

bool Admin::check_in(const string &password)
{
	if (password == _password)
		return true;
	return false;
}

void Admin::add_book(LibMat &libmat)
{
	cout << space << "书名:";
	string book_name;
	cin >> book_name;
	if (libmat.find_book(book_name))
	{
		cout << space << "该书已在库中！" << endl;
		return;
	}
	cout << space << "作者:";
	string autor_name;
	cin >> autor_name;
	cout << space << "总量:";
	int sum;
	cin >> sum;
	libmat.add_book(book_name, autor_name, sum);
	cout << space << "添加" << book_name << "成功！" << endl;
}

void Admin::change_book(LibMat &libmat)
{
	string book_name;
	book_name = find_book(libmat);
	cout << space << "按任意键继续...";
	_getch();
	bool go_for_it = true;
	if (!book_name.empty())
	{
		int pos=1;
		char ch = ' ';
		string new_name;
		int number;
		display_change_menu();
		cout << space;
		do
		{
			ch = enter_judge(4, display_change_menu, pos);
			switch (ch)
			{
			case'1':cout << space << "请输入更正的书名:";
				    cin >> new_name;
					libmat.change_book(book_name, new_name, "", -1); 
					book_name = new_name;
					break;
			case'2':cout << space << "请输入更正的作者名:";
				    cin >> new_name;
				    libmat.change_book(book_name, "", new_name,-1); break;
			case'3':cout << space << "请输入更正的数量:";
			    	cin >> number;
			    	libmat.change_book(book_name, "", "", number); break;
			case'4':go_for_it = false; break;
			default:cout << space << "输入有误，键入回车以继续！" << endl; cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}	    //清除输入缓存区的内容  
			if (go_for_it)
				cout << space << "请继续操作:";
		} while (go_for_it);
	}
	display_littlemenu1(3);
}

void Admin::remove_book(LibMat &libmat)
{
	string book_name;
	book_name = find_book(libmat);
	if (!book_name.empty())
	{
		char ch;
		cout << space << "是否删除?(Y/N):";
		cin >> ch;
		if (ch == 'Y' || ch == 'y')
		{
			libmat.remove_book(book_name);
			cout << space << "删除成功！" << endl;
		}
	}
	cout << space << "按任意键继续...";
	_getch();
	display_littlemenu1(1);
}

string Admin::find_book(LibMat &libmat,bool display )
{
	display_choise_menu();
	cout << space;
	char ch = ' ';
	int pos = 1;
	ch = enter_judge(2, display_choise_menu, pos);
	string book_name;
	string autor_name;
	int sum;
	switch (ch)
	{
	case'1':cout << space << "请输入书名:";
		    cin >> book_name;
		    if (!libmat.find_book(book_name))
		    {
			     cout << space << "该书不在库中！" << endl;
				 cout << space << "按任意键继续...";
				 _getch();
				 if (display)
					 display_littlemenu1(1);
			     return "";
			}
			autor_name = libmat.b_find_a(book_name); break;
	case'2':cout << space << "请输入作者:";//仅提供每个作者只有一本书的版本
			cin >> autor_name;
			if (!libmat.find_autor(autor_name))
			{
				cout << space << "该作者不在库中!" << endl;
				cout << space << "按任意键继续...";
				_getch();
				if (display)
					display_littlemenu1(1);
				return "";
			}
			book_name = libmat.a_find_b(autor_name);
	        break;
	default:cout << space << "输入有误，键入回车以继续！" << endl; cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}	    //清除输入缓存区的内容  
	sum = libmat.num_of_book(book_name);
	cout << space << "Find it!" << "\n"
		<< space << "┌─────────────┬──────────┬────┐\n"
		<< space << "│           书名           │        作者        │ 馆藏量 │\n"
		<< space << "├─────────────┼──────────┼────┤\n"
		<< space << "│";
	print_table(book_name, 26);
	print_table(autor_name, 20);
	print_table(sum, 8);
	cout << "\n"
		<< space << "└─────────────┴──────────┴────┘\n";
	if(display)
		display_littlemenu1(1);
	return book_name;
}

void Admin::add_student()
{
	cout << space << "学号:";
	string id;
	cin >> id;
	if (check_student(id))
	{
		cout << space << "该用户已存在！" << endl;
		return;
	}
	cout << space << "名字:";
	string user_name;
	cin >> user_name;
	cout << space << "学院:";
	string academe;
	cin >> academe;
	_student_id.push_back(id);
	_student_name.push_back(user_name);
	_student_academe.push_back(academe);
	vector<string> vec;
	_student_book.push_back(vec);
	_student_password[id] = "000000";
	cout << space << "添加学生用户\"" << user_name << "\"成功！" << endl;
}

bool Admin::check_student(std::string & id)
{
	vector<string>::iterator beg_id = _student_id.begin();
	vector<string>::iterator end_it = _student_id.end();
	for (; beg_id != end_it; ++beg_id)
		if (*beg_id == id)
			return true;
	return false;
}

void Admin::remove_student()
{
	viterator_v vec;
	vv_iterator book;
	vec=find_student(book);
	if (!vec.empty())
	{
		cout << space << "是否移除?(Y/N):";
		char ch;
		cin >> ch;
		if (ch == 'y' || ch == 'Y')
		{
			map<string, string>::iterator it;
			it = _student_password.find(*vec[0]);
			if (it != _student_password.end())
				_student_password.erase(it);
			_student_id.erase(vec[0]);
			_student_name.erase(vec[1]);
			_student_academe.erase(vec[2]);
			_student_book.erase(book);
			cout << space << "移除成功！" << endl;
		}
	}
}

viterator_v &Admin::find_student(vv_iterator &beg_book)
{
	static vector<vector<string>::iterator> vec;  //用于返回多组iterator
	cout << space << "请输入该学生的学号:";
	string id;
	cin >> id;
	if (!check_student(id))
	{
		cout << space << "该用户不存在！" << endl;
		return vec;
	}
	vector<string>::iterator beg_name = _student_name.begin();
	vector<string>::iterator beg_id = _student_id.begin();
	vector<string>::iterator beg_academe = _student_academe.begin();
	beg_book = _student_book.begin();
	vector<string>::iterator end_it = _student_id.end();
	for (; beg_id != end_it; ++beg_id, ++beg_name, ++beg_academe, ++beg_book)
	{
		if (*beg_id == id)
		{
			cout << space << "Find it!\n"
				<< space << "┌──────┬──────┬──────────┐\n"
				<< space << "│    学号    │    姓名    │        学院        │\n"
				<< space << "├──────┼──────┼──────────┤\n"
				<< space << "│";
			print_table(*beg_id, 12);
			print_table(*beg_name, 12);
			print_table(*beg_academe, 20);
			cout << "\n"
				<< space << "└──────┴──────┴──────────┘"
				<< endl;
			vec.push_back(beg_id);
			vec.push_back(beg_name);
			vec.push_back(beg_academe);
			return vec;
		}
	}
	return vec;
}

bool Admin::check_teacher(std::string & id)
{
	vector<string>::iterator beg_id = _teacher_id.begin();
	vector<string>::iterator end_it = _teacher_id.end();
	for (; beg_id != end_it; ++beg_id)
		if (*beg_id == id)
			return true;
	return false;
}

void Admin::add_teacher()
{
	cout << space << "工号:";
	string id;
    cin >> id;
	if (check_teacher(id))
	{
		cout << space << "该用户不存在！" << endl;
		return;
	}
	cout << space << "名字:";
	string user_name;
	cin >> user_name;
	_teacher_id.push_back(id);
	_teacher_name.push_back(user_name);
	vector<string> vec;
	_teacher_book.push_back(vec);
	_teacher_password[id] = "000000";
	cout << space << "添加教师用户\"" << user_name << "\"成功！" << endl;
}


void Admin::remove_teacher()
{
	viterator_v vec;
	vv_iterator book;
	vec = find_teacher(book);
	if (!vec.empty())
	{
		cout << space << "是否移除?(Y/N):";
		char ch;
		cin >> ch;
		if (ch == 'y' || ch == 'Y')
		{
			map<string, string>::iterator it;
			it = _teacher_password.find(*vec[0]);
			if(it!=_teacher_password.end())
				_teacher_password.erase(it);
			_teacher_id.erase(vec[0]);
			_teacher_name.erase(vec[1]);
			_teacher_book.erase(book);
			cout << space << "移除成功！" << endl;
		}
	}
}

viterator_v &Admin::find_teacher(vv_iterator &beg_book)
{
	static vector<vector<string>::iterator> vec;  //用于返回多组iterator
	cout << space << "请输入该教师的工号:";
	string id;
	cin >> id;
	if (!check_teacher(id))
	{
		cout <<space << "该用户不存在" << endl;
		return vec;
	}
	vector<string>::iterator beg_name = _teacher_name.begin();
	vector<string>::iterator beg_id = _teacher_id.begin();
	beg_book = _teacher_book.begin();
	vector<string>::iterator end_it = _teacher_id.end();
	for (; beg_id != end_it; ++beg_id, ++beg_name, ++beg_book)
	{
		if (*beg_id == id)
		{
			cout << space << "Find it!\n"
				<< space << "┌──────┬──────┐\n"
				<< space << "│    工号    │    姓名    │\n"
				<< space << "├──────┼──────┤\n"
				<< space << "│";
			print_table(*beg_id, 12);
			print_table(*beg_name, 12);
			cout << "\n"
				<< space << "└──────┴──────┘"
				<< endl;
			vec.push_back(beg_id);
			vec.push_back(beg_name);
			return vec;
		}
	}
	return vec;
}

void Admin::display_student()
{
	int sum=0;
	vector<string>::iterator beg_name = _student_name.begin();
	vector<string>::iterator beg_id = _student_id.begin();
	vector<string>::iterator beg_academe = _student_academe.begin();
	vector<string>::iterator end_it = _student_id.end();
	cout << space << "┌──────┬──────┬──────────┐\n"
		 << space << "│    学号    │    姓名    │        学院        │\n";
	for (; beg_id != end_it; ++beg_id, ++beg_name, ++beg_academe)
	{
		sum++;
		cout << space << "├──────┼──────┼──────────┤\n"
			 << space << "│";
		print_table(*beg_id, 12);
		print_table(*beg_name, 12);
		print_table(*beg_academe, 20);
		cout << endl;
	}
	cout << space << "├──────┴──────┴──────────┤\n"
		 << space << "│        用户总人数          ";
	print_table(sum, 20);
	cout <<'\n'
		 << space << "└────────────────────────┘"
		 << endl;
}

void Admin::display_teacher()
{
	int sum = 0;
	vector<string>::iterator beg_name = _teacher_name.begin();
	vector<string>::iterator beg_id = _teacher_id.begin();
	vector<string>::iterator end_it = _teacher_id.end();
	cout << space << "┌──────┬──────┐\n"
		 << space << "│    工号    │    姓名    │\n";
	for (; beg_id != end_it; ++beg_id, ++beg_name)
	{
		cout << space << "├──────┼──────┤\n"
			<< space  << "│";
		print_table(*beg_id, 12);
		print_table(*beg_name, 12);
		cout << endl;
		sum++;
	}
	cout << space << "├──────┴──────┤\n"
		 << space << "│ 用户总人数   ";
	print_table(sum, 12);
	cout <<'\n'
		 << space << "└─────────────┘"
		 << endl;
}

void Admin::change_password()
{
	bool try_again;
	do
	{
		try_again = false;
		cout << space << "请输入新密码( 6位 ) :";
		string password;
		password = in_password();
		while (password.empty())
		{
			cout <<'\n'<< space << "输入有误，请重新输入:";
			password = in_password();
		}
		cout << '\n' << space << "确 认 密 码 ( 6位 ) :";
		string password_temp;
		password_temp = in_password();
		while (password_temp.empty())
		{
			cout << '\n' << space << "输入有误，请重新输入:";
			password_temp = in_password();
		}
		if (password != password_temp)
		{
			cout << '\n' << space << "密码不一致！请重试。\n";
			try_again = true;
		}
		else
			_password = password;
	} while (try_again);
	cout << '\n' << space << "修改成功，请牢记你新的密码！" << endl;
}

bool Admin::delete_all_data(LibMat &libmat)
{
	cout << space << "所有数据都将被销毁且不可恢复，你确定要去新世界吗？(Y/N):";
	char ch;
	cin >> ch;
	if (ch == 'Y' || ch == 'y')
	{
		_password = "000000";
		_student_id.clear();
		_student_name.clear();
		_student_academe.clear();
		_student_book.clear();
		_student_password.clear();
		_teacher_id.clear();
		_teacher_name.clear();
		_teacher_book.clear();
		_teacher_password.clear();
		libmat.delete_all_data();
		cout << space << "啊~整个世界都清净了!!!\n"
			<< space << "按任意键继续...";
		_getch();
		return true;
	}
	return false;
}

void Admin::check_out( bool student,bool teacher,bool password)
{
	if (student)
	{
		ofstream outfile("student_data.dat");
		if (!outfile)
			cerr << space << "Oops!Cannot open the file" << endl;
		else
		{
			vector<string>::iterator beg_name = _student_name.begin();
			vector<string>::iterator beg_id = _student_id.begin();
			vector<string>::iterator beg_academe = _student_academe.begin();
			vector<vector<string> >::iterator beg_book = _student_book.begin();
			vector<string>::iterator end_it = _student_id.end();
			for (; beg_id != end_it; ++beg_id, ++beg_name, 
				  ++beg_academe, ++beg_book)
			{
				outfile << *beg_id << ' ' << left << setw(12)
					<< *beg_name << ' ' << setw(20) << *beg_academe << ' ';
				vector<string>::iterator beg = (*beg_book).begin();
				vector<string>::iterator end_book = (*beg_book).end();
				for (; beg != end_book; ++beg)
					outfile << *beg << ' ';
				outfile << endl;
			}
		}
		outfile.close();
		outfile.open("student_password.dat");
		if (!outfile)
			cerr << space << "Oops!Cannot open the file" << endl;
		else
		{
			vector<string>::iterator beg_id = _student_id.begin();
			vector<string>::iterator end_it = _student_id.end();
			for (; beg_id != end_it; ++beg_id)
				outfile << *beg_id << ' ' << _student_password[*beg_id] 
				        << endl;

		}
		outfile.close();
	}

	if (teacher)
	{
		ofstream outfile("teacher_data.dat");
		if (!outfile)
			cerr << space << "Oops!Cannot open the file" << endl;
		else
		{
			vector<string>::iterator beg_name = _teacher_name.begin();
			vector<string>::iterator beg_id = _teacher_id.begin();
			vector<vector<string> >::iterator beg_book = _teacher_book.begin();
			vector<string>::iterator end_it = _teacher_id.end();
			for (; beg_id != end_it; ++beg_id, ++beg_name, ++beg_book)
			{
				outfile << *beg_id <<' '<<left
					    <<setw(12)<< *beg_name << ' ';			
				vector<string>::iterator beg = (*beg_book).begin();
				vector<string>::iterator end_book = (*beg_book).end();
				for (; beg != end_book; ++beg)
					outfile << *beg << ' ';
				outfile << endl;
			}
		}
		outfile.close();
		outfile.open("teacher_password.dat");
		if (!outfile)
			cerr << space << "Oops!Cannot open the file" << endl;
		else
		{
			vector<string>::iterator beg_id = _teacher_id.begin();
			vector<string>::iterator end_it = _teacher_id.end();
			for (; beg_id != end_it; ++beg_id)
				outfile << *beg_id << ' ' << _teacher_password[*beg_id] 
				        << endl;
		}
		outfile.close();
	}
	if (password)
	{
		ofstream outfile("admin_password.dat");
		if (!outfile)
			cerr << space << "Oops!Cannot open the file" << endl;
		else
		{
			outfile << _password;
		}
	}
}
