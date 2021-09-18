#include "csapp.h"
int main()
{
    string x,type,readok;
    cin>>x;
    char name[100],time[100];
    strcpy(name,x.c_str());
    DIR* dirs=opendir(name);
    struct dirent *dep;
    while((dep =readdir(dirs))!=NULL)
    {
        printf("Found file: %s\n", dep->d_name);
    }
    closedir(dirs);
    return 0;
}