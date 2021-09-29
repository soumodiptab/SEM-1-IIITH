#include<bits/stdc++.h>
using namespace std;
#define sizee 100
template <class T, class V>
class unorderedmap
{
    public:
    long long int val = 31;
    long long int sized = sizee;
    class node
    {
        public:
        T key;
        V value;
        node* next;
    }; // closing of node class
    node *arr[sizee];
    unorderedmap()
    {
        long long int i = 0;
        while(i<sized)
        {
            arr[i] = NULL;
            i++;
        }
    } // closing of class constructor
    long long int hashingvalue(T key)
    {
        ostringstream cal;
        cal << key;
        long long int tat = 1;
        long long int hashing = 0;
        string t = cal.str();
        long long int i = 0;
        while(i<t.size())
        {
            hashing += (t[i]*tat);
            hashing %= sized;
            tat *= val;
            i++;
        }
        return hashing;
    } // closing of hashingvalue function
   node *getnewNode(T key, V value)
   {
       node* pq = new node;
       pq->key = key;
       pq->value = value;
       pq->next = NULL;
       return pq;
   } // closing of getnewNode
   void insert(T key, V value)
   {
       long long int place = hashingvalue(key);
       node *head = arr[place];
       if(head == NULL)
       {
           node *pq = getnewNode(key,value);
           arr[place] = pq;
           return;
       }
       else if(head ->next == NULL)
       {
           if(head->key == key)
           return;
           else
           {
               node* pq = getnewNode(key,value);
               head->next = pq;
               return;
           }
           
       }// closing of else if
       else
       {
           node *temp = head;
           while(temp->next != NULL)
           {
               if(temp->key == key)
               {
                   return;
               }
               else
               {
                   temp = temp->next;
               }
               
           } // closing of while
           if(temp ->key == key)
           {
               return;
           }
           node *pq = getnewNode(key,value);
           temp->next = pq;
           return;
       } // closing of else
       return;
       
   }// closing of insert function
   pair<bool , V> search(T key)
   {
       long long int place = hashingvalue(key);
       node *head = arr[place];
       pair<bool,V>result;
       if(head == NULL)
       {
           result.first = false;
           return result;
       }
       else
       {
           node *temp = head;
           while(temp!= NULL)
           {
               if(temp->key == key)
               {
                   result = {true,temp->value};
                   return result;
               } // closing of if
               else
               {
                   temp = temp->next;
               }
               
           }//closing of while
           result.first = false;
           return result;
       } // closing of else
       
   }// closing of function
   void deletevalue(T key)
   {
       long long int place = hashingvalue(key);
       node* head = arr[place];
       node* temp = head;
       node *prev = NULL;
       if(head == NULL)
       {
           cout<<"No data for key"<<endl;
           return;
       }
       else
       {
           if(head->key == key)
           {
               temp = head;
               head = head->next;
               arr[place] = head;
               delete(temp);
               return;
           }
           while(temp->next != NULL && temp->key != key)
           {
               prev = temp;
               temp = temp->next;
           } // closing of while
           if(temp ->next == NULL && temp->key != key)
           {
               cout<<"No data"<<endl;
           }
           else
           {
               prev->next = temp->next;
               delete(temp);
           }
           
       }// close of else
       return;
   }// close of function
   void print()
   {
       unsigned long long int i = 0;
       while(i<sizee)
       {
          
           node* temp = arr[i];
           if(temp != NULL)
           {while(temp!= NULL)
           {
               cout<<"->"<<temp->key<<"="<<temp->value;
               temp = temp->next;
           }
           cout<<endl;
           }
           i++;
       }
   } // closing of print function

};
int main ()
{   
    string s;
    string input;
    unorderedmap<string,string>t;
    int val;
    cin>>val;
    while(val--)
    {
        int ch;
        cin>>ch;
        if(ch == 1)
        {
            cin>>s;
            cin>>input;
            t.insert(s,input);
            t.print();
        }
        else if(ch == 2)
        {
            cin>>s;
            t.deletevalue(s);
            t.print();
        }
        else if(ch == 3)
        {
            cin>>s;
            pair<bool,string>result = t.search(s);
            if(result.first == true)
            {
                cout<<"True"<<endl;
            }
            else
            {
                cout<<"False"<<endl;
            }
            
        }
        else if (ch == 4)
        {
            cin>>s;
            pair<bool,string>result = t.search(s);
            if(result.first == true)
            {
                cout<<result.second<<endl;
            }
            else
            {
                cout<<"Not found"<<endl;
            }
            
        }
    
    } // closing of loop
    return 0;

} // closing of main