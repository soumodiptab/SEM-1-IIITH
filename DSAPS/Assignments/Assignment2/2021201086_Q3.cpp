#include<iostream>
using namespace std;
template <typename T>
class deque
{
    T* data;
    bool clear_flag=false;
    int t_size,capacity;
    int p_front,rear;
    //-----------------------------------------------------------------
    void init()
    {
        p_front=-1;
        rear=-1;
        data= new T[capacity];
    }
    void enlarge()
    {// check for complexity later on free vs delete []
        capacity*=2;
        T* temp=new T[capacity];
        int i,pos;
        i=p_front;
        pos=capacity/4;
        for(int j=pos;j<pos+t_size;j++)
        {
            temp[j]=data[i];
            i=(i+1)%(capacity/2);
        }
        p_front=pos;
        rear=pos+t_size-1;
        T* del=data;
        delete [] del;
        data=temp;
    }
    public:
    deque()
    {
        t_size=0;
        capacity=10;
        init();
    }
    deque(int n,T val)
    {
        t_size=n;
        capacity=n*2;
        init();
        int x=n/2;
        for(int i=x;i<x+t_size;i++)
        {
            data[i]=val;
        }
        p_front=x;
        rear=x+t_size-1;
    }
    ~deque()
    {
        delete [] data;
    }
    void push_back(T val)
    {
        if(t_size==capacity)
        {
            enlarge();
            rear++;
        }
        else if(rear==-1)
        {
            rear=p_front=(capacity/2);
        }
        else
        {
            rear=(rear+1)%capacity;
        }
        data[rear]=val;
        t_size++;
    }
    void pop_back()
    {
        if(t_size==0)
            return;
        if(t_size==1)
        {
            p_front=rear=-1;
        }
        else if(rear==0)
        {
            rear=capacity-1;
        }
        else
        {
            rear--;
        }
        t_size--;
    }
    void push_front(T val)
    {
        if(t_size==capacity)
        {
            enlarge();
            p_front--;
        }
        else if(p_front==-1)
        {
            rear=p_front=(capacity/2);
        }
        else if(p_front==0)
        {
            p_front=capacity-1;
        }
        else
        {
            p_front--;
        }
        data[p_front]=val;
        t_size++;
    }
    void pop_front()
    {
        if(t_size==0)
            return;
        if(t_size==1)
        {
            p_front=rear=-1;
        }
        else if(p_front==capacity-1)
        {
            p_front=0;
        }
        else
        {
            p_front++;
        }
        t_size--;
    }
    T front()
    {
        if(t_size==0)
            return NULL;
        return data[p_front];
    }
    T back()
    {
        if(t_size==0)
            return NULL;
        return data[rear];
    }
    bool empty()
    {
        return (t_size==0)?true:false;
    }
    int size()
    {
        return this->t_size;
    }
    void resize(int new_size,T default_val)
    {
        if(new_size>capacity)
        {
            enlarge();
        }
        if(new_size>t_size)
        {
            int diff=new_size-t_size;
            while(diff--)
            {
                push_back(default_val);
            }
        }
        else if(new_size<t_size)
        {
            int diff=t_size-new_size;
            while(diff--)
            {
                pop_back();
            }
        }
    }
    void clear()
    {
        clear_flag=true;
        t_size=0;
        p_front=rear=-1;
    }
    T operator [](int index)
    {
        if(index>=t_size)
            return NULL;
        int pos=(p_front+index)%capacity;
        return data[pos];
    }
    void display()
    {
        int pos=p_front;
        for(int i=0;i<t_size;i++)
        {
            cout<<data[pos]<<" ";
            pos=(pos+1)%capacity;
        }
        cout<<endl;
    }
};
void testcases()
{
    deque<int>q(2,10);
    q.display();
    q.push_front(12);
    q.display();
    q.push_front(21);
    q.display();
    q.push_back(23);
    q.display();
    q.resize(10,5);
    q.display();
    q.push_back(13);
    q.display();
    q.resize(6,1);
    q.display();
}
int main()
{
    testcases();
    return 0;
}