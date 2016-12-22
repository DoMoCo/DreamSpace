#include<iostream>
#include<ctime>
#include<cstdlib>
#include<iomanip>
#include<Windows.h>
using namespace std;
void show_my_sweatheart(int *sweatheart,int times)//秀恩爱
{
	cout << "    ┏━━━┓\n"
		  << "    ┃" << sweatheart[0] << ' ' << sweatheart[1] << "  " << sweatheart[2] << "┃\n"
		  << "    ┃" << sweatheart[3] << ' ' << sweatheart[4] << "  " << sweatheart[5] << "┃"
	     << "\t\t 第" << setw(2) <<times<< "次相遇\n"
		  << "    ┃" << sweatheart[6] << ' ' << sweatheart[7] << "  " << sweatheart[8] << "┃"
		  << " \t    试问人生能有几次相遇？\n"
		  << "    ┗┳━┳┛\n"
		  << "       ┤├\n\n";
}
void sweat_life()                           //默然相爱，寂静欢喜
{
	bool Intimacy = true,Passion = true,Commitment = true;//亲密、激情、承诺缺一不可
	int days = 0;                            //爱情长跑的天数 
	while (Intimacy || Passion || Commitment)//爱情的经营
	{
		days+=60;
		cout << "     第" << setw(3) << days << " 天  ";
		if (!(rand() % 2)&&Intimacy)
			Intimacy = false, cout   << "失了亲密  ";
		if (!(rand() % 2)&& Passion)
			Passion = false, cout    << "少了激情  ";
		if (!(rand() % 2)&& Commitment)
			Commitment = false, cout << "没了承诺  ";
		if (Intimacy && Passion && Commitment)
			cout << "如胶似漆·形影不离";
		cout << endl;
	}                                //爱情三角奔溃之时，爱情的巨轮也将黯然触礁
	cout << "\n     曾经的海誓山盟，如今的劳燕分飞，有些人，一旦失去，便是一辈子\n"
		  << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
}
int main()
{
	int greatest_love[9];            //greatest_love代表至爱
	int new_sweatheart[9],times=1;   //new_sweatheart代表新的恋人、time代表相遇的次数
	for (int i = 0; i < 9; ++i)
		greatest_love[i] = rand() % 2;//毫无疑问，每个人心中那个至爱的人都是不一样的
	cout << "\n     >那个我至爱的人<\n";
	show_my_sweatheart(greatest_love,1);
	sweat_life();
	Sleep(5000);                     //让我等等那迟到的爱情
	srand(time(NULL));
	int sth_in_common;               //两个人相同的地方
	cout<< "    ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n"
	    << "━━┫曾经无数次的回眸，才换来今生的一次相遇，爱情，求不得，求之不得┣━━━━━"
	    << "    ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
	while (true)                     //无休止的循环，在爱与被爱间重复的一生
	{
		times++;
		sth_in_common = 0;
		Sleep((rand() % 10 + 1) * 1000);//未知的时间
		for (int i = 0; i < 9; ++i)    //未知的人
		{
			new_sweatheart[i] = rand() % 2;
			if (greatest_love[i] == new_sweatheart[i])
				sth_in_common++;         //相同的地方+1 
		}
		if (sth_in_common >= 5)        //请让我找到至爱的影子
		{
			cout << "     我的恋人,每月的情人节，让我送你一支玫瑰花\n";
			show_my_sweatheart(new_sweatheart,times);
			sweat_life();
		}
		else                           //原谅我不能将就
		{
			show_my_sweatheart(new_sweatheart,times);
			cout << "     咫尺天涯，能够相遇，已是不易，而你，注定要从我的全世界路过，我不能将就\n"
				  << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
		}
		if (GetAsyncKeyState(VK_ESCAPE))//漫漫人生路，如果你哪天再也爱不动了，请按下Esc键
			break;                               
	}
	cout << "    青梅枯萎，竹马老去，从此爱上的每一个人都像你\n"
		  << "    所谓伊人，在水一方，从此爱上的每一个人都像你\n"
	  	  << "    此去经年，红烛依旧，从此爱上的每一个人都像你\n\n"
		  << "    愿那些我爱过的的人一切安好，愿那个我至爱的人一生幸福...\n\n\n\n";
	system("pause");
	return 0;
}

