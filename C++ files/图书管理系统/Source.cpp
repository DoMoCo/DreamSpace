#include<iostream>
#include"User.h"
#include"func.h"
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#undef max        //ȡ��windows.h��max�ĺ궨�壬window.h��limits����max�����˶���
#include<limits>  //���������ظ�����Ĵ���
using namespace std;
#define space "\t\t\t\t\t\t"//�������λ��

void borrow_book(User &user, LibMat &libmat);//����
void return_book(User &user, LibMat &libmat);//����
void addfile();//���ļ������ڣ���ӱ�Ҫ�ļ�
void display_start();//��ӡʹ��˵��
void admin_in(LibMat &libmat);//����Ա����&&����
void user_in(LibMat &libmat, bool user);//ѧ��||��ʦ����
void user_func(LibMat &libmat, User &user, int pos);//ѧ��||��ʦ����
void feedback();//�������

void borrow_book(User &user,LibMat &libmat)
{
	bool borrow_it = true;//��¼�Ƿ����
	bool is_in = false;
	cout << space << "��������Ҫ�������:";
	string book_name;
	cin >> book_name;
	is_in = user.is_borrow(book_name);
	if (is_in)
		cout <<space << "���Ѿ������Ȿ�飡\n";
	else
	{
		bool find_it = libmat.find_book(book_name);
		if (find_it)
		{
			string autor_name = libmat.b_find_a(book_name);
			int number = libmat.num_of_book(book_name);
			print_book(book_name, autor_name, number);//��ӡ�鼮��Ϣ
			cout << space << "�Ƿ����?(Y/N):";
			char ch;
			cin >> ch;
			if (ch == 'n' || ch == 'N')
				borrow_it = false;
			if (borrow_it)
			{
				user.borrow_book(book_name);//����
				libmat.borrow_book(book_name);//����鼮�Ĺݲ�������
				cout << space << "���ĳɹ���" << endl;
			}
		}
		else
			cout << space << "Sorry," << book_name << "is unavailable!" 
			     << endl;
	} 
}

void return_book(User &user,LibMat &libmat)
{
	bool is_in;//��¼�Ȿ���Ƿ��ѽ�
	string book_name;
	do
	{
		cout << space << "��������Ҫ�黹������:";
		cin >> book_name;
		is_in = user.is_borrow(book_name);
		if (!is_in)
			cout << space << "��û�н��Ȿ�飡\n";
	} while (!is_in);
	user.return_book(book_name);
	libmat.return_book(book_name);
	cout << space << "�黹�ɹ�!" << endl;
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
	cout << space << " ������������������������������\n"
		 << space << " ��\n"      
		 << space << " ��       ����˵��:\n"
		 << space << " �� ��     1�������ͨ��������\n"
		 << space << " �� ��        w��s���ƶ�ѡ���\n"
		 << space << " �� ȫ     2����Enter��Space��\n"
		 << space << " �� ��        ����dȷ������\n"
	 	 << space << " �� ��     3����Esc��a�������\n"
		 << space << " �� ��     4����Ȼ��Ҳ����ͨ��\n"
		 << space << " �� ��        �������+Enter��\n"
		 << space << " �� ��        ѡ����\n"
		 << space << " �� ��     5�������û�Ĭ������\n"
		 << space << " �� ��        Ϊ000000\n"
		 << space << " �� ��     6����������ʱ�����\n"
		 << space << " �� ��        ������\n"
		 << space << " ��\n"
	     << space << " ��\n";
	cout << space << " �밴���������...";
	_getch();
}

void admin_in(LibMat &libmat)
{
	Admin admin;
	vector<vector<string> >::iterator book;//���ڴ���find_student��find_teacher����
	bool student = false;                  //��¼ѧ�������Ƿ��޸ģ��޸��򱣴�
	bool teacher = false;				   //��¼��ʦ�����Ƿ��޸�
	bool save_password = false;			   //��¼�����Ƿ��޸�
	cout << space << "���������Ա������(6λ):";
	string password;
	password = in_password();//��������
	while (password.empty())
	{
		cout<<'\n' << space << "�� �� �� ������������:";
		password = in_password();
	}
	bool check_success = admin.check_in(password);
	if (check_success)
	{
		cout<<'\n' << space << "����ɹ������Ժ�...";
		Sleep(1000);          //�ȴ�1��
		bool end_it = true;   //�ж��Ƿ��������
		bool back = false;    //�жϲ����Ƿ�ص�����Ա�ĳ�ʼ����(�зֲ˵�)
		display_admin_menu(); //��ӡ����Ա��������
		cout << space;
		int pos_1 = 1, pos_2 = 1, pos_3 = 1;//��¼�ϴ�ѡ����λ�ã���ʼΪ1
		char ch = ' ';        //��¼ѡ��Ĺ���
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
						 default: cout << space << "��������,����س��Լ�����" << endl; 
							      cin.clear();
								  cin.ignore(numeric_limits<streamsize>::max(), '\n');
						 }//������뻺����(��ǰ��)
						 if (!back)
							 cout << space << "���������:";
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
						 default: cout << space << "�������󣬼���س��Լ�����" << endl; 
						 cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
						 }
						 if (!back)
							 cout << space << "���������:";
					 } while (!back);
					 break;
			case'6': admin.change_password(); save_password = true; break;
			case'7': end_it = !admin.delete_all_data(libmat); 
				     student = true;
				     teacher = true;
					 save_password = true; break;
			case'8': system("cls"); display_admin_menu(); pos_1 = 1; break;
			case'9': end_it = false; break;
			default: cout << space << "�������󣬼���س��Լ�����" << endl; cin.clear();
				     cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}	     
			if (end_it)
				cout << space << "���������:";
		} while (end_it);
		admin.check_out(student,teacher,save_password);//��������
		system("cls");//ˢ��
		display_main_menu(1);//��ӡ���˵���ѡ���λ��Ϊ1
	}
	else
		cout<< " ������󣬻��췦��!!!" << endl;
}

void user_in(LibMat &libmat, bool user)
{
	if (user)
	{
		cout << space << "�� �� �� �� �� ѧ ��:";
		string user_id;
		cin >> user_id;
		Student student(user_id);
		user_func(libmat, student, 2);
	}
	else
	{
		cout << space << "�� �� �� �� �� �� ��:";
		string user_id;
		cin >> user_id;
		Teacher teacher(user_id);
		user_func(libmat, teacher, 3);
	}
}

void user_func(LibMat &libmat, User &user,int pos)
{                                //pos��¼���˵�ѡ���λ��
	bool save_me = true;         //��¼�Ƿ������Լ�������
	cout << space << "������������� (6λ):";
	string password;
	password = in_password();
	while (password.empty())
	{
		cout <<'\n'<< space << "������������������:";
		password = in_password();
	}
	bool check_success = user.check_in(password);
	if (check_success)
	{
		cout <<'\n'<< space << "����ɹ������Ժ�..." ;
		Sleep(1000);
		bool end_it = true;
		display_user_menu();
		cout << space;
		int pos_1 = 1;//��¼ѡ���λ��
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
			default:cout << space << "�������󣬼���س��Լ�����" << endl; cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}	    //������뻺����������     
			if (end_it)
				cout << space << "���������:";
		} while (end_it);
		user.check_out(save_me,true);//��������
		system("cls");
		display_main_menu(pos);//��ӡ���˵���ѡ���λ��Ϊ2��3
	}
	else if ((user.user_name()).empty())
		cout << " �˺Ų����ڣ��첦�����ǵĿͷ�����ע���˺Űɣ�\n";
	else
		cout << " �������\n"
	         << space << "����ϵ����Ա,�����www.tobethebest.cn�޸�������롣";
}

void feedback()//�����д�����->���Ĳ��ô���
{
	bool good_back = true;//�ж���û�໰
	cout << space << "������������:";
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
		cout << space << "���ǻἰʱ������������лл��ķ�����" << endl;
	else
		cout << space << "��ʹ���������" << endl;
	cout << space << "�����������...";
	_getch();
	display_main_menu(4);//��ӡ���˵���ѡ���λ��Ϊ4
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
		default:cout << space << "�������󣬼���س��Լ�����" << endl;

			cin.clear();cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}	    //������뻺����������,��ֹ�ַ�Ϊ'\n'�����������ַ�������޽�   
		if (end_it)
			cout << space << "���������:";
	} while (end_it);
	libmat.check_out();//����ͼ������
	cout << space<<"��ӭ�ٴη��ʣ�";
	system("pause");
	return 0;
}

