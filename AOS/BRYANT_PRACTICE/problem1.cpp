#include "iostream"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
void fun()
{
    int fd1, fd2;
    fd1 = open("randomfile.txt", O_RDONLY, 0);
    printf("fd2 = %d\n", fd1);
    close(fd1);
    fd2 = open("baz.txt", O_RDONLY, 0);
    printf("fd2 = %d\n", fd2);
    exit(0);
}
int main(void)
{
    char c;
    //reads stdin and writes in std out
    std::cout<<getpid()<<"\n";
    while(read(STDIN_FILENO, &c, 1) != 0)
        write(STDOUT_FILENO, &c, 1);
    exit(0);

}