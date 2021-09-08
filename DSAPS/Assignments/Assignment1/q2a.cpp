#include<iostream>
#include<unordered_map>
using namespace std;
/*
cap=3
map keys:
| 2 | 3 | 4 |
DLL:
front            rear
-----   -----   -----
| 2 |<->| 3 |<->| 4 |
-----   -----   -----
First build operations:
1>insert at rear
2>delete from anywhere
3>get value from key
4>set key,value
*/
//Doubly linked list
class Node
{
    public:
    int key;
    int val;
    Node* left;
    Node* right;
    //Initialize the pointers with NULL
    Node(int key,int value)
    {
        this->key=key;
        val=value;
        left=NULL;
        right=NULL;
    }
    Node(int key)
    {
        this->key=key;
        left=NULL;
        right=NULL;
    }
};
class LRU{
    Node* front;
    Node* rear;
    int cap,size;
    unordered_map<int,Node*> mp;
    public:
    void insert_node(Node* new_node)
    {//Insert ar rear
        //No node present
        if(front==NULL)
        {
            front=new_node;
            rear=front;
        }
        else
        {
            rear->right=new_node;
            new_node->left=rear;
            rear=new_node;
        }
    }
    void delete_node(Node* target)
    {//delete from : <front> <middle> <rear>
        if(target->left == NULL)//i.e. front node
        {
            front=target->right;
        }
        if(target->right == NULL)//i.e. rear node
        {
            rear=target->left;
        }
        //for middle nodes
        if(target->left != NULL)
            target->left->right=target->right;
        if(target->right != NULL)
            target->right->left=target->left;
        free(target);
    }
    LRU(int capacity)
    {
        cap=capacity;
        size=0;
        front=NULL;
        rear=NULL;
    }
    int get(int key)
    {
        if(mp.find(key)==mp.end()) // if key not found
        {
            return -1;
        }
        //if key found
        int val=mp[key]->val;
        delete_node(mp[key]);
        Node *temp=new Node(key,val);
        mp[key]=temp;
        insert_node(temp);
        return val;
    }
    void set(int key,int val)
    {
        if(cap<=0)
            return;
        Node *new_node=new Node(key,val);
        if(mp.find(key)!=mp.end())//key is already present
        {// remove from DLL , insert at rear
            delete_node(mp[key]);
            insert_node(new_node);
        }
        else//if key is not present
        {
            if(size==cap)//if cap reached then remove front and insert rear
            {
                int temp_key=front->key;
                delete_node(front);
                insert_node(new_node);
                mp.erase(temp_key);
            }
            else//cap not reached then just insert
            {
                insert_node(new_node);
                size++;
            }
        }
        mp[key]=new_node;
    }
    void print_dll()//print the dll
    {
        Node *temp=front;
        while(temp!=NULL)
        {
            cout<<temp->val<<" ";
            temp=temp->right;
        }
        cout<<endl;
    }
};
void LL_testcases()
{
    Node* n1=new Node(1,2);
    Node* n2=new Node(2,3);
    Node* n3=new Node(3,4);
    Node* n4=new Node(4,5);
    LRU cache(3);
    cache.insert_node(n1);
    cache.insert_node(n2);
    cache.insert_node(n3);
    cache.insert_node(n4);
    cache.print_dll();
    cache.delete_node(n2);
    cache.print_dll();
    cache.delete_node(n4);
    cache.print_dll();
    cache.delete_node(n3);
    cache.print_dll();
    cache.delete_node(n1);
    cache.print_dll();
}
void cachetest()
{
    LRU cache(3);
    cache.set(1,1);
    cache.set(2,2);
    cache.set(3,3);
    cache.set(4,4);
    cout<<cache.get(1)<<endl;
    cout<<cache.get(2)<<endl;
    cout<<cache.get(3)<<endl;
    cout<<"--------------------"<<endl;
    cache.set(2,5);
    cout<<cache.get(2)<<endl;
    cache.set(5,5);
    cout<<cache.get(2)<<endl;

}
void driver()
{
    
}
int main()
{
    //LL_testcases();
    cachetest();

    return 0;
}