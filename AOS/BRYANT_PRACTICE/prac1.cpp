#include "csapp.h"
#define DEF_MODE S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH
int main()
{
    string x="Hello world.";
    char a[100];
    strcpy(a,x.c_str());
    auto fd = open("newfile.txt", O_CREAT|O_TRUNC|O_WRONLY, DEF_MODE);
    int y=write(fd,a,x.length());
    printf("%d\n",y);
    mkdir("hello",0777);
    return 0;
}