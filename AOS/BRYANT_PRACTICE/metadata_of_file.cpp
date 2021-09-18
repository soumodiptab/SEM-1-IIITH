#include "csapp.h"
int main()
{
    struct stat filestat;
    string x,type,readok;
    cin>>x;
    char name[100],time[100];
    strcpy(name,x.c_str());
    stat(name,&filestat);
    if (S_ISREG(filestat.st_mode))
    /* Determine file type */
        type = "regular";
    else if (S_ISDIR(filestat.st_mode))
        type = "directory";
    else
        type = "other";
    if ((filestat.st_mode & S_IRUSR)) /* Check read access */
        readok = "yes";
    else
        readok = "no";
    printf("%lld.%.9ld", (long long)filestat.st_mtim.tv_sec, filestat.st_mtim.tv_nsec);
    cout<<" type = "<<type<<" read: "<<readok<<"\n";
    return 0;
}