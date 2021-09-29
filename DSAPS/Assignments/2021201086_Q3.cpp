#include<iostream>
using namespace std;
template <typename T>
class deque
{
    T* data;
    int size,capacity;
    int front,rear;
    //-----------------------------------------------------------------
    deque()
    {
        size=0;
        capacity=10;
        front=-1;
        rear=-1;
    }
    deque(int n,T x)
    {
        size=n;
        capacity=n;
    }
    ~deque()
    {
        delete [] data;
    }
};
void testcases()
{

}
int main()
{
    testcases();
    return 0;
}