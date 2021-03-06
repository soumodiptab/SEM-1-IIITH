#include <bits/stdc++.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include<sys/wait.h> 
#include <sys/types.h>
#include <fcntl.h>
#define esc 27
#define cls printf("%c[2J", esc)
#define pos() printf("%c[%d;%dH", esc, xcor, ycor)
#define posx(x,y) printf("%c[%d;%dH", esc, y, x)
using namespace std;
struct termios old_terminal;
struct termios new_terminal;
void highlight_red(string message)
{
	cout<<"\033[0;31m";
    cout<<message;
	cout<<"\033[0m";
}
void highlight_green(string message)
{
    cout<<"\033[0;32m";
    cout<<message;
    cout<<"\033[0m";
}
void enter_raw_mode()
{
    tcgetattr(STDIN_FILENO, &old_terminal);
    new_terminal = old_terminal;
    new_terminal.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_terminal);//changes will occur after flush
}
void exit_raw_mode()
{
    tcsetattr(STDIN_FILENO,TCSANOW,&old_terminal);//changes will occur now
}
void moveCursor(int x,int y) {
	cout<<"\033["<<x<<";"<<y<<"H";
}
void clear_line()
{
    cout<<"\033[K";
}
void arrow()
{
    highlight_green("<-");
}
void hide_cursor()
{
    cout<<"\e[?25l";
}
void show_cursor()
{
    cout<<"\e[?25h";
}
int main()
{
    char ch;
    enter_raw_mode();
    highlight_red("hello");
    cout<<endl;
    highlight_green("world");
    cout<<endl;
    cls;
    posx(0,1);
    cout<<"hello";
    posx(0,2);
    cout<<"world";
    posx(0,3);
    cls;
    moveCursor(1,0);
    hide_cursor();
    arrow();
    int min=1,max=5,i=1;
    while((ch=cin.get())!='q')
    {
        if(ch=='k' && i>min)
        {
            moveCursor(i,0);
            clear_line();
            i--;
            moveCursor(i,0);
            arrow();
        }
        if(ch=='l' && i<=max)
        {
            moveCursor(i,0);
            clear_line();
            i++;
            moveCursor(i,0);
            arrow();
        }
        if(ch=='c')
        {
            moveCursor(i,0);
            clear_line();
        }
        if(ch=='f')
        {
            cout<<"\b";
        }
        cout<<ch;
    }
    show_cursor();
    cls;
    exit_raw_mode();
    return 0;
}