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
using namespace std;
struct termios old_terminal;
struct termios new_terminal;
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
//x is row and y is
void moveCursor(int x,int y) {
	cout<<"\033["<<x<<";"<<y<<"H";
}
void clear_line()
{
    cout<<"\033[K";
}
void arrow()
{
    highlight_green("*");
}
int main()
{
    char ch;
    enter_raw_mode();
    cls;
    moveCursor(1,0);
    arrow();
    int min=1,max=5,i=1;
    //navigate k and l
    while((ch=cin.get())!='q')
    {
        if(ch=='k' && i>min)//move up
        {
            moveCursor(i,0);
            clear_line();
            i--;
            moveCursor(i,0);
            arrow();
        }
        if(ch=='l' && i<=max)//move down
        {
            moveCursor(i,0);
            clear_line();
            i++;
            moveCursor(i,0);
            arrow();
        }
        if(ch=='c')//clear line
        {
            moveCursor(i,0);
            clear_line();
        }
        if(ch=='f')//backspace test
        {
            cout<<"\b";
        }
    }
    cls;
    exit_raw_mode();
    return 0;
}