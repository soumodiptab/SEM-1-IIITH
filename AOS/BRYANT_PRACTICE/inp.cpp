#include<stdio.h>
#include<iostream>
#define esc 27
#define cls printf("%c[2J", esc)
#define pos() printf("%c[%d;%dH", esc, xcor, ycor)
#define posx(x,y) printf("%c[%d;%dH", esc, y, x)
using namespace std;

void showError(string str)
{
	//clearCommand();
	cout<<endl;
	cout<<"\033[0;31m"<<str<<endl;
	cout<<"\033[0m";
	cout<<":";
}

int main()
{
    char ch;
    /*showError("hello");
    getchar();
    cls;
    posx(0,1);
    cout<<"hello";
    posx(0,2);
    cout<<"world";
    posx(0,3);*/
    while((ch=getchar())!=0)
    {
        cout<<(int)ch<<endl;
    }
    return 0;
}