#include<stdio.h>
#include<iostream>
using namespace std;
int main()
{
    char ch;
    while((ch=getchar())!=0)
    {
        cout<<(int)ch<<endl;
    }
    return 0;
}