#include "csapp.h"
#include<iomanip>
#define DEF_MODE S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH
void temp()
{
    string x="Hello world.";
    char a[100];
    strcpy(a,x.c_str());
    auto fd = open("newfile.txt", O_CREAT|O_TRUNC|O_WRONLY, DEF_MODE);
    int y=write(fd,a,x.length());
    printf("%d\n",y);
    mkdir("hello",0777);
}
int main()
{
    cout<<setw(6)<<"hello"<<endl;
    float var = 37.66666;
    // Directly print the number with .2f precision
    cout << setw(6)<< fixed << setprecision(2) << var<<endl;
    cout<<"\033[36m";
    cout << "hello"<<endl;
    cout<<"\033[0m";
    cout<<endl;
    cout<<setw(10);
    cout<<"\033[32m";
    cout<<"/\\56"<<endl;
    cout<<"./"<<endl;
    cout << '\a';
    cout<<endl;
    char ch;
    ch=cin.get();
    while(ch!='q')
    {
        ch=cin.get();
        cout<<ch<<endl;
    }
    return 0;
}