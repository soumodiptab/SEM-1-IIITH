#include<iostream>
#include<unordered_map>
using namespace std;
class Node
{
    public:
    int key;
    Node* left;
    Node* right;
    Node(int key)
    {
        this->key=key;
        left=NULL;
        right=NULL;
    }
};
class hashed_list
{
    /*
    stuff to make :
    front and rear
    insert node at rear
    erase function or delete any node
    */
    int sz=0;
    private:
    Node* front;
    Node* rear;
    unordered_map<int,Node*>mp;
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
        delete target;
    }
    public:
    int head()
    {
        if(front!=NULL)
            return front->key;
        return -1; 
    }
    void insert(int key)
    {
        if(mp.find(key)!=mp.end())
            return;
        Node *new_node=new Node(key);
        mp[key]=new_node;
        insert_node(new_node);
        sz++;
    }
    void erase(int key)
    {
        if(mp.find(key)==mp.end())
            return;
        delete_node(mp[key]);
        mp.erase(key);
        sz--;
    }
    int size()
    {
        return sz;
    }
};
class LFU{
    int cap,size,min_freq;
    unordered_map<int,pair<int,int>>key_map;
    unordered_map<int,hashed_list>freq_list;
    public:
    LFU(int capacity)
    {
        size=0;
        cap=capacity;
    }
    int get(int key)
    {
        if(cap==0||key_map.find(key)==key_map.end())
        {
            return -1;
        }
        int count=key_map[key].second;
        key_map[key].second++;
        freq_list[count].erase(key);
        if(freq_list[count].size()==0)
        {
            freq_list.erase(count);
            if(count==min_freq)
                    min_freq++;
        }
        freq_list[count+1].insert(key);
        return key_map[key].first;
    }
    void set(int key,int val)
    {
        if(cap==0)
            return;
        if(key_map.find(key)!=key_map.end())
        {
            int count=key_map[key].second;
            key_map[key]=make_pair(val,count+1);
            freq_list[count].erase(key);
            if(freq_list[count].size()==0)
            {
                freq_list.erase(count);
                if(count==min_freq)
                    min_freq++;
            }
            freq_list[count+1].insert(key);
        }
        else
        {
            if(size==cap)
            {
                int target=freq_list[min_freq].head();
                freq_list[min_freq].erase(target);
                key_map.erase(target);
            }
            else
            {
                size++;
            }
            key_map[key]=make_pair(val,1);
            freq_list[1].insert(key);
            min_freq=1;
        }
        
    }

};
void cachetest()
{
    LFU cache(3);
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
int main()
{
    cachetest();
    return 0;
}