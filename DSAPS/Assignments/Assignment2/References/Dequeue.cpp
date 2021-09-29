include<iostream>
using namespace std;
template <typename Type>
struct node
{
Type val;
node<Type>* prev = NULL;
node<Type>* next = NULL;
 };

 template <typename Type>
 class deque
 {  private:
    node<Type>* m_front = NULL;
    node<Type>* m_rear = NULL;
     long long int count =0;
 public:
   deque();
  deque(Type key);
  deque(int n,Type x);
 void push_back(Type X);
 void pop_back();
 void push_front(Type x);
 void pop_front ();
Type back();
Type front();
 bool empty();
 int size();
 void resize(int x, Type d);
 void clear();
 Type D(int x);
 void display();
 };
 template <typename Type>
 void deque<Type>::display()
 {
     node<Type>* temp = new node<Type>();
     temp = m_front;
     while(temp!=NULL)
     {
         cout<<temp->val<<" ";
         temp = temp->next;
     }
     cout<<endl;
 }
 template <typename Type>
 bool deque<Type>::empty()
 {
 if(m_rear == NULL)
  return true;
  return false;
  }
 template <typename Type>
 int deque<Type>::size()
 {
 return count;
 }
 template <typename Type>
 void deque<Type>::resize(int x,Type d)
 {
 if(x>count)
 {

 if(m_front == NULL)
 { node<Type>* temp = new node<Type>();
 temp->val = d;
 m_front = temp;
 m_rear = m_front;
     temp->next = NULL;
     temp->prev = NULL;
     count++;
 }
 while(count<x)
 {
 node<Type>*semp = new node<Type>();
 semp->val = d;
 m_rear->next = semp;
 semp->prev = m_rear;
 semp->next = NULL;
 m_rear = semp;
 count++;
 }
 }
 else
 {
 while(count>x)
 {
 node<Type>*temp = m_front;
 m_front = m_front->next;
 m_front->prev = NULL;
 delete (temp);
 count--;
 }
 m_front->prev = NULL;
 }
 }
 template <typename Type>
 void deque<Type>::clear()
 {
 while(m_front!=NULL)
 {
 node<Type>* temp = m_front;
 m_front = m_front->next;
 delete(temp);
 }
 count = 0;
 }
 template <typename Type>
  deque<Type>::deque()
 {
   m_front = NULL;
   m_rear = NULL;
 }
 template <typename Type>
 void deque<Type>::pop_back()
 { if(m_rear==NULL)
    return;
 node<Type>* temp = m_rear;
 m_rear = m_rear->prev;
 if(m_rear!=NULL){
 m_rear->next = NULL;}
 delete(temp);
 count--;
 }
 template <typename Type>
 void deque<Type>::pop_front()
 {
 if(m_front == NULL)
 return;
 node<Type>* temp = m_front;
 m_front = temp->next;
 delete(temp);
 if(m_front!=NULL)
 {m_front->prev = NULL;}
 count--;
 }
 template <typename Type>
 void deque<Type>::push_front(Type d)
 {
 node<Type>*temp = new node<Type>();
 temp->val = d;
 if(m_front == NULL)
 {
 m_front = temp;
 m_rear = temp;
 temp->next = NULL;
 temp->prev = NULL;
 count++;}
 else
 {
 temp->next = m_front;
 m_front->prev = temp;
 temp->prev = NULL;
 m_front = temp;
 count++;
 }
 }
 template <typename Type>
 void deque<Type>::push_back(Type d)
 {
 node<Type>*temp = new node<Type>();
 temp->val = d;
 if(m_front == NULL)
 {
 m_front = temp;
 m_rear = temp;
 temp->next = NULL;
 temp->prev = NULL;
 count++;
 }
 else
 {
 m_rear->next = temp;
 temp->prev = m_rear;
 temp->next = NULL;
 m_rear = temp;
 count++;
 }
 }
 template <typename Type>
 Type deque<Type>::front()
 {
     return m_front->val;
 }
 template <typename Type>
 Type deque<Type>::back()
 {
    return m_rear->val;
  }
 template <typename Type>
 deque<Type>::deque(int n,Type x)
 {
 node<Type> *temp = new node<Type>();
 temp->val = x;
 if(m_front == NULL)
 {
 m_front = temp;
 m_rear = temp;
 temp->next = NULL;
 temp->prev = NULL;
 count++;
 }
 else
 {
 m_rear->next = temp;
 temp->prev = m_rear;
 temp->next = NULL;
count++; m_rear = temp;
}
n--;
while (n--)
{
node<Type> *temp = new node<Type>();
temp->val = x;
m_rear->next = temp;
temp->prev = m_rear;
count++;
m_rear = temp;
}
}
template <typename Type>
Type deque<Type>::D(int n)
{
int tot = 0;
if(count == 0)
	return "-1";
node<Type>* temp = m_front;
if(n>count)
return "-1";
if(n == count-1)
return m_rear->val;
if(n==0)
return m_front->val;
while(tot<n)
{
temp = temp->next;
tot++;

}
return temp->val;
}
int main()
{ 
deque<string> *arr =NULL;
    int Q,c,n;
    string x;
    cin>>Q;
    while (Q--){      
 
 cin>>c;

 switch (c)
 {

 case 1: cin>>x;
         arr->push_front(x);  
         arr->display();

         break;
 case 2: arr->pop_front();
         arr->display();
         break;
 
 case 3: cin>>x;
         arr->push_back(x);
         arr->display();
         break;
 
 case 4: arr->pop_back();
         arr->display();
         break;
 
 case 5: if(arr !=NULL)
         delete arr;
         arr = new deque<string>();
         break;

 case 6: cin>>n>>x;
         if(arr !=NULL)
         delete arr;
         arr = new deque<string>(n,x);
         arr->display();
         break;

 case 7: cout<<arr->front()<<endl;
         break;

 case 8: cout<<arr->back()<<endl;
         break;
 
 case 9: if(arr->empty())
          cout<<"true\n";
         else
          cout<<"false\n";
         break;

 case 10: cout<<arr->size()<<endl;
          break;

 case 11: cin>>n>>x;
          arr->resize(n,x);
          arr->display();
          break;

 case 12: arr->clear();
          break;
 
 case 13: cin>>n;
          cout<<arr->D(n)<<endl;
          break;

 case 14: arr->display();
         break;

 default:
     break;
 }
    }


delete arr;
return 0;
}