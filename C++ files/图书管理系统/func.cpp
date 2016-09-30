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
	cout << "��";
}

void print_table(int sum, int length)
{
	int space_table=0;
	int temp = sum;
	while (temp >= 10)//ȡ������λ��
	{
		temp /= 10;
		space_table++;
	}
	space_table++;
	int len = (length-space_table )/ 2;//�۰봦��ʹ�ڱ�����־���
	for (int ix = 0; ix < len; ++ix)
		cout << ' ';
	cout << sum;
	len = length - space_table - len;
	for (int ix = 0; ix < len; ++ix)
		cout << ' ';
	cout << "��";
}

void print_book(const string book_name,const string autor_name,int number)
{
	cout << space << "Find it!" << "\n"
		<< space << "�����������������������������Щ��������������������Щ���������\n"
		<< space << "��           ����           ��        ����        �� �ݲ��� ��\n"
		<< space << "�����������������������������੤�������������������੤��������\n"
		<< space << "��";
	print_table(book_name, 26);
	print_table(autor_name, 20);
	print_table(number, 8);
	cout <<"\n"
		<< space <<"�����������������������������ة��������������������ة���������\n";
}

string in_password()
{
	int i=0;
	char ch;
	char passwd[7] = {' '};
	while ((ch = _getch()) != '\r'&&i<7)
	{
		if (ch != 8)//���ǻس���¼��
		{
			passwd[i] = ch;
			putchar('*');//�������*��
			i++;
		}
		else
		{
			putchar('\b'); //������ɾ��һ��������ͨ������س��� /b���س�һ��
			putchar(' '); //����ʾ�ո���Ѹղŵ�*����ס��
			putchar('\b');//Ȼ���ٻس�һ��ȴ�¼�롣
			i--;
		}
	}
	if(i==6)//������ȷ������ַ���������
		passwd[i] = '\0';
	else
		return "";
	char *cp = passwd;
	string password(passwd);
	return password;
}

char enter_judge(int end_pos, void(*display)(int), int &beg_pos)//����ѡ��ĺ���
{
	bool go_for_it = true;//�����������ѭ������Ȼ����Ҳ�ʺ���goto
	char func = ' ';
	char ch_1, ch_2, ch_temp;
	char end_it;          //��ǽ�������������
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
			case 72:  if (beg_pos > 1)         //�����ϼ�
						  beg_pos--;
					  else
						  beg_pos = end_pos;
					  break;
			case 80:  if (beg_pos<end_pos)
						  beg_pos++;
					  else
						  beg_pos = 1;
					  break;        //�����¼�
			case 75:  func = end_it; go_for_it = false;
				      break;                     //�������
			case 77:  if (beg_pos < 10)        //�����Ҽ�
						  func = beg_pos + 48;//0->'1'��'2'��'3'...
					  else
						  func = beg_pos + 87;//0->'a'��'b'��'c'...
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
		case 0x1B:func = end_it; go_for_it = false; break;//Esc������ǰѡ��
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
			cout << space << "���������:";
		}	
	}
	cout << endl;
	return func;
}

void display_main_menu(int pos )
{
	system("cls");
	cout     << "\n\t\t\t\t\t" <<"        ��������������������������\n"
		     << space << "��������������������������\n"
		     << space << "����      ���˵�      ����\n";
	if (pos == 1)
		cout << space << "���Ʃ������������������Ω�\n"
			 << space << "����  1������Ա����   ����\n"
			 << space << "���ũ������������������ͩ�\n"
			 << space << "����  2��ѧ������     ����\n";
	else
		cout << space << "�����������������������ȩ�\n"
			 << space << "����  1������Ա����   ����\n";
	if (pos == 2)
		cout << space << "���Ʃ������������������Ω�\n"
			 << space << "����  2��ѧ������     ����\n"
			 << space << "���ũ������������������ͩ�\n"
			 << space << "����  3����ʦ����     ����\n";
	else if (pos != 1)
		cout << space << "�����������������������ȩ�\n"
			 << space << "����  2��ѧ������     ����\n";
	if (pos == 3)
		cout << space << "���Ʃ������������������Ω�\n"
			 << space << "����  3����ʦ����     ����\n"
			 << space << "���ũ������������������ͩ�\n"
			 << space << "����  4���������     ����\n";
	else if (pos != 2)
		cout << space << "�����������������������ȩ�\n"
			 << space << "����  3����ʦ����     ����\n";
	if (pos == 4)
		cout << space << "���Ʃ������������������Ω�\n"
			 << space << "����  4���������     ����\n"
			 << space << "���ũ������������������ͩ�\n"
			 << space << "����  5���˳�         ����\n";
	else if (pos != 3)
		cout << space << "�����������������������ȩ�\n"
			 << space << "����  4���������     ����\n";
	if (pos == 5)
		cout << space << "���Ʃ������������������Ω�\n"
			 << space << "����  5���˳�         ����\n"
			 << space << "��������������������������";
	else if (pos != 4)
		cout << space << "�����������������������ȩ�\n"
			 << space << "����  5���˳�         ����\n"
			 << space << "��������������������������";
	else
		cout << space << "��������������������������";
	cout << "\n\t\t\t\t\t" << "        ��������������������������\n";
}

void display_admin_menu(int pos )
{
	system("cls");
	cout     << space << "����������������������\n"
			 << space << "��   �����ǹ���Ա   ��\n";
	if (pos == 1)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 1�� �鿴�鼮��Ϣ ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 2�� �鿴ѧ���û� ��\n";
	else
		cout << space << "����������������������\n"
			 << space << "�� 1�� �鿴�鼮��Ϣ ��\n";
	if (pos == 2)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 2�� �鿴ѧ���û� ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 3�� �鿴��ʦ�û� ��\n";
	else if (pos != 1)
		cout << space << "����������������������\n"
			 << space << "�� 2�� �鿴ѧ���û� ��\n";
	if (pos == 3)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 3�� �鿴��ʦ�û� ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 4�� �鼮����     ��\n";
	else if (pos != 2)
		cout << space << "����������������������\n"
			 << space << "�� 3�� �鿴��ʦ�û� ��\n";
	if (pos == 4)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 4�� �鼮����     ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 5�� �û�����     ��\n";
	else if (pos != 3)
		cout << space << "����������������������\n"
			 << space << "�� 4�� �鼮����     ��\n";
	if (pos == 5)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 5�� �û�����     ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 6�� �޸�����     ��\n";
	else if (pos != 4)
		cout << space << "����������������������\n"
			 << space << "�� 5�� �û�����     ��\n";
	if (pos == 6)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 6�� �޸�����     ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 7�� ������       ��\n";
	else if (pos != 5)
		cout << space << "����������������������\n"
			 << space << "�� 6�� �޸�����     ��\n";
	if (pos == 7)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 7�� ������       ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 8�� ˢ��         ��\n";
	else if (pos != 6)
		cout << space << "����������������������\n"
			 << space << "�� 7�� ������       ��\n";
	if (pos == 8)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 8�� ˢ��         ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 9�� �ص����˵�   ��\n";
	else if (pos != 7)
		cout << space << "����������������������\n"
			 << space << "�� 8�� ˢ��         ��\n";
	if (pos == 9)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 9�� �ص����˵�   ��\n"
			 << space << "����������������������\n";
	else if (pos != 8)
		cout << space << "����������������������\n"
			 << space << "�� 9�� �ص����˵�   ��\n"
			 << space << "����������������������\n";
	else
		cout << space << "����������������������\n";
}

void display_littlemenu1(int pos )
{
	system("cls");
	if (pos == 1)
		cout << space << "����������������������\n"
			 << space << "�� 1�� �����鼮     ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 2�� ����鼮     ��\n";
	else
		cout << space << "����������������������\n"
			 << space << "�� 1�� �����鼮     ��\n";
	if (pos == 2)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 2�� ����鼮     ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 3�� �޸��鼮��Ϣ ��\n";
	else if (pos != 1)
		cout << space << "����������������������\n"
			 << space << "�� 2�� ����鼮     ��\n";
	if (pos == 3)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 3�� �޸��鼮��Ϣ ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 4�� ɾ���鼮     ��\n";
	else if (pos != 2)
		cout << space << "����������������������\n"
			 << space << "�� 3�� �޸��鼮��Ϣ ��\n";
	if (pos == 4)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 4�� ɾ���鼮     ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 5�� �ص���һ��   ��\n";
	else if (pos != 3)
		cout << space << "����������������������\n"
			 << space << "�� 4�� ɾ���鼮     ��\n";
	if (pos == 5)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 5�� �ص���һ��   ��\n"
			 << space << "����������������������\n";
	else if (pos != 4)
		cout << space << "����������������������\n"
			 << space << "�� 5�� �ص���һ��   ��\n"
			 << space << "����������������������\n";
	else
		cout << space << "����������������������\n";
}

void display_littlemenu2(int pos )
{
	system("cls");
	if (pos == 1)
		cout << space << "����������������������\n"
			 << space << "�� 1�� ����ѧ���û� ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 2�� ���ѧ���û� ��\n";
	else
		cout << space << "����������������������\n"
			 << space << "�� 1�� ����ѧ���û� ��\n";
	if (pos == 2)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 2�� ���ѧ���û� ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 3�� �Ƴ�ѧ���û� ��\n";
	else if (pos != 1)
		cout << space << "����������������������\n"
			 << space << "�� 2�� ���ѧ���û� ��\n";
	if (pos == 3)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 3�� �Ƴ�ѧ���û� ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 4�� ���ҽ�ʦ�û� ��\n";
	else if (pos != 2)
		cout << space << "����������������������\n"
			 << space << "�� 3�� �Ƴ�ѧ���û� ��\n";
	if (pos == 4)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 4�� ���ҽ�ʦ�û� ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 5�� ��ӽ�ʦ�û� ��\n";
	else if (pos != 3)
		cout << space << "����������������������\n"
			 << space << "�� 4�� ���ҽ�ʦ�û� ��\n";
	if (pos == 5)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 5�� ��ӽ�ʦ�û� ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 6�� �Ƴ���ʦ�û� ��\n";
	else if (pos != 4)
		cout << space << "����������������������\n"
			 << space << "�� 5�� ��ӽ�ʦ�û� ��\n";
	if (pos == 6)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 6�� �Ƴ���ʦ�û� ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 7�� �ص���һ��   ��\n";
	else if (pos != 5)
		cout << space << "����������������������\n"
			 << space << "�� 6�� �Ƴ���ʦ�û� ��\n";
	if (pos == 7)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 7�� �ص���һ��   ��\n"
			 << space << "����������������������\n";
	else if (pos != 6)
		cout << space << "����������������������\n"
			 << space << "�� 7�� �ص���һ��   ��\n"
			 << space << "����������������������\n";
	else
		cout << space << "����������������������\n";
}

void display_user_menu(int pos )
{
	system("cls");
	cout	 << space << "����������������������\n"
			 << space << "��    �����û�    ��\n";
	if (pos == 1)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 1�� �鿴������Ϣ ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 2�� �鿴�ҵ���Ϣ ��\n";
	else
		cout << space << "����������������������\n"
			 << space << "�� 1�� �鿴������Ϣ ��\n";
	if (pos == 2)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 2�� �鿴�ҵ���Ϣ ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 3�� ����         ��\n";
	else if (pos != 1)
		cout << space << "����������������������\n"
			 << space << "�� 2�� �鿴�ҵ���Ϣ ��\n";
	if (pos == 3)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 3�� ����         ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 4�� ����         ��\n";
	else if (pos != 2)
		cout << space << "����������������������\n"
			 << space << "�� 3�� ����         ��\n";
	if (pos == 4)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 4�� ����         ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 5�� �޸ĵ������� ��\n";
	else if (pos != 3)
		cout << space << "����������������������\n"
			 << space << "�� 4�� ����         ��\n";
	if (pos == 5)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 5�� �޸ĵ������� ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 6�� ���Ӳ������� ��\n";
	else if (pos != 4)
		cout << space << "����������������������\n"
			 << space << "�� 5�� �޸ĵ������� ��\n";
	if (pos == 6)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 6�� ���Ӳ������� ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 7�� ˢ��         ��\n";
	else if (pos != 5)
		cout << space << "����������������������\n"
			 << space << "�� 6�� ���Ӳ������� ��\n";
	if (pos == 7)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 7�� ˢ��         ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 8�� �ص����˵�   ��\n";
	else if (pos != 6)
		cout << space << "����������������������\n"
			 << space << "�� 7�� ˢ��         ��\n";
	if (pos == 8)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 8�� �ص����˵�   ��\n"
			 << space << "����������������������\n";
	else if (pos != 7)
		cout << space << "����������������������\n"
			 << space << "�� 8�� �ص����˵�   ��\n"
			 << space << "����������������������\n";
	else
		cout << space << "����������������������\n";
}

void display_choise_menu(int pos)
{
	system("cls");
	cout	 << space << "����������������������\n"
			 << space << "��  ��ѡ����ҷ�ʽ  ��\n";
	if (pos == 1)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 1�� ������       ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 2�� ������       ��\n";
	else
		cout << space << "����������������������\n"
			 << space << "�� 1�� ������       ��\n";
	if (pos == 2)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 2�� ������       ��\n"
			 << space << "����������������������\n";
	else if (pos != 1)
		cout << space << "����������������������\n"
			 << space << "�� 2�� ������       ��\n"
			 << space << "����������������������\n";
	else
		cout << space << "����������������������\n";
}

void display_change_menu(int pos)
{
	system("cls");
	cout	 << space << "����������������������\n"
			 << space << "��  ��ѡ���޸���Ŀ  ��\n";
	if (pos == 1)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 1�� ����         ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 2�� ������       ��\n";
	else
		cout << space << "����������������������\n"
			 << space << "�� 1�� ����         ��\n";
	if (pos == 2)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 2�� ������       ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 3�� �ݲ���       ��\n";
	else if (pos != 1)
		cout << space << "����������������������\n"
			 << space << "�� 2�� ������       ��\n";
	if (pos == 3)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 3�� �ݲ���       ��\n"
			 << space << "�ũ�������������������\n"
			 << space << "�� 4�� �ص���һ��   ��\n";
	else if (pos != 2)
		cout << space << "����������������������\n"
			 << space << "�� 3�� �ݲ���       ��\n";
	if (pos == 4)
		cout << space << "�Ʃ�������������������\n"
			 << space << "�� 4�� �ص���һ��   ��\n"
			 << space << "����������������������\n";
	else if (pos != 3)
		cout << space << "����������������������\n"
			 << space << "�� 4�� �ص���һ��   ��\n"
			 << space << "����������������������\n";
	else
		cout << space << "����������������������\n";
}