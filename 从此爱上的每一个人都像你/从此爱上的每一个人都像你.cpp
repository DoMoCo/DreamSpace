#include<iostream>
#include<ctime>
#include<cstdlib>
#include<iomanip>
#include<Windows.h>
using namespace std;
void show_my_sweatheart(int *sweatheart,int times)//�����
{
	cout << "    ����������\n"
		  << "    ��" << sweatheart[0] << ' ' << sweatheart[1] << "  " << sweatheart[2] << "��\n"
		  << "    ��" << sweatheart[3] << ' ' << sweatheart[4] << "  " << sweatheart[5] << "��"
	     << "\t\t ��" << setw(2) <<times<< "������\n"
		  << "    ��" << sweatheart[6] << ' ' << sweatheart[7] << "  " << sweatheart[8] << "��"
		  << " \t    �����������м���������\n"
		  << "    ���ש��ש�\n"
		  << "       �ȩ�\n\n";
}
void sweat_life()                           //ĬȻ�మ���ž���ϲ
{
	bool Intimacy = true,Passion = true,Commitment = true;//���ܡ����顢��ŵȱһ����
	int days = 0;                            //���鳤�ܵ����� 
	while (Intimacy || Passion || Commitment)//����ľ�Ӫ
	{
		days+=60;
		cout << "     ��" << setw(3) << days << " ��  ";
		if (!(rand() % 2)&&Intimacy)
			Intimacy = false, cout   << "ʧ������  ";
		if (!(rand() % 2)&& Passion)
			Passion = false, cout    << "���˼���  ";
		if (!(rand() % 2)&& Commitment)
			Commitment = false, cout << "û�˳�ŵ  ";
		if (Intimacy && Passion && Commitment)
			cout << "�罺���ᡤ��Ӱ����";
		cout << endl;
	}                                //�������Ǳ���֮ʱ������ľ���Ҳ����Ȼ����
	cout << "\n     �����ĺ���ɽ�ˣ���������ַɣ���Щ�ˣ�һ��ʧȥ������һ����\n"
		  << "��������������������������������������������������������������������������������\n";
}
int main()
{
	int greatest_love[9];            //greatest_love��������
	int new_sweatheart[9],times=1;   //new_sweatheart�����µ����ˡ�time���������Ĵ���
	for (int i = 0; i < 9; ++i)
		greatest_love[i] = rand() % 2;//�������ʣ�ÿ���������Ǹ��������˶��ǲ�һ����
	cout << "\n     >�Ǹ�����������<\n";
	show_my_sweatheart(greatest_love,1);
	sweat_life();
	Sleep(5000);                     //���ҵȵ��ǳٵ��İ���
	srand(time(NULL));
	int sth_in_common;               //��������ͬ�ĵط�
	cout<< "    ������������������������������������������������������������������\n"
	    << "���������������εĻ������Ż���������һ�����������飬�󲻵ã���֮���éǩ���������"
	    << "    ������������������������������������������������������������������\n";
	while (true)                     //����ֹ��ѭ�����ڰ��뱻�����ظ���һ��
	{
		times++;
		sth_in_common = 0;
		Sleep((rand() % 10 + 1) * 1000);//δ֪��ʱ��
		for (int i = 0; i < 9; ++i)    //δ֪����
		{
			new_sweatheart[i] = rand() % 2;
			if (greatest_love[i] == new_sweatheart[i])
				sth_in_common++;         //��ͬ�ĵط�+1 
		}
		if (sth_in_common >= 5)        //�������ҵ�������Ӱ��
		{
			cout << "     �ҵ�����,ÿ�µ����˽ڣ���������һ֧õ�廨\n";
			show_my_sweatheart(new_sweatheart,times);
			sweat_life();
		}
		else                           //ԭ���Ҳ��ܽ���
		{
			show_my_sweatheart(new_sweatheart,times);
			cout << "     ������ģ��ܹ����������ǲ��ף����㣬ע��Ҫ���ҵ�ȫ����·�����Ҳ��ܽ���\n"
				  << "��������������������������������������������������������������������������������\n";
		}
		if (GetAsyncKeyState(VK_ESCAPE))//��������·�������������Ҳ�������ˣ��밴��Esc��
			break;                               
	}
	cout << "    ��÷��ή��������ȥ���Ӵ˰��ϵ�ÿһ���˶�����\n"
		  << "    ��ν���ˣ���ˮһ�����Ӵ˰��ϵ�ÿһ���˶�����\n"
	  	  << "    ��ȥ���꣬�������ɣ��Ӵ˰��ϵ�ÿһ���˶�����\n\n"
		  << "    Ը��Щ�Ұ����ĵ���һ�а��ã�Ը�Ǹ�����������һ���Ҹ�...\n\n\n\n";
	system("pause");
	return 0;
}

