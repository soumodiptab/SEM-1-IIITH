#include <signal.h>
#include <sys/ioctl.h>
#include <iostream>
void hello()
{
    std::cout<<"hello world\n";
}
void sighandler(int n){
    std::cout << "test" << std::endl;
    hello();
}
int main(){
    signal(SIGWINCH, sighandler);
    while(getchar())
    {
        std::cout<<"still inside loop\n";
    }
    return 0;
}