#include<iostream>
using namespace std;
/**
 * @brief Hash Map with O(1) complexity uses Chaining
 * 
 * @tparam T key value <typename>
 * @tparam V Value corresponding to key <class/typename>
 */
template <typename T,class V>
class unordered_map
{
    const static int MAX_BUCKET_SIZE=20;
    const int prime=31;
    class Node
    {
        public:
        T key;
        V value;
        Node* prev;
        Node* next;
        Node(T key,V value)
        {
            this->key=key;
            this->value=value;
            prev=NULL;
            next=NULL;
        }
    };
    //util functions:
    Node *buckets[MAX_BUCKET_SIZE]={NULL};
    int hash_function(T key)
    {
        long long int hashed_value=0;
        string key_string=to_string(key);
        long long int factor = 1;
        for (char letter : key_string)
        {
            hashed_value = (hashed_value + (letter * factor) % MAX_BUCKET_SIZE) % MAX_BUCKET_SIZE;
            factor = (factor * prime) % MAX_BUCKET_SIZE;
        }
        return hashed_value;
    }
    Node* find_node(T key)
    {
        int position=hash_function(key);
        Node *iter=buckets[position];
         while(iter!=NULL && iter->key!=key)
        {
            iter=iter->next;
        }
        return iter;
    }
    public:
    void insert(T key, V value)
    {
        int position=hash_function(key);//find using hashing
        Node* new_node=new Node(key,value);
        Node* head=buckets[position];
        if(head != NULL)
        {
            new_node->next=head;
            head->prev=new_node;
        }
        buckets[position]=new_node;
    }
    void erase(T key)
    {
        int position=hash_function(key);//hashing
        Node *iter=buckets[position];
        Node *head=iter;
        //Key does not exist
        if(iter==NULL)
            return;
        //key may exist
        while(iter!=NULL && iter->key!=key)
        {
            iter=iter->next;
        }
        //key does not exist
        if(iter==NULL)
            return;
        //key exists
        if(iter->prev !=NULL)
            iter->prev->next=iter->next;
        if(iter->next !=NULL)
            iter->next->prev=iter->prev;
        if(head->key==iter->key)
            buckets[position]=NULL;
        delete iter;
    }
    bool find(T key)
    {
        return (find_node(key)!=NULL)?true:false;
    }
    V &operator [](T key)
    {
        Node* temp=find_node(key);
        return temp->value;
    }
    void debug()
    {
        for(int i=1;i<40;i++)
        {
            cout<<i<<" "<<hash_function(i)<<endl;
        }
    }
};
void testcases()
{
    unordered_map<int,int>mp;
    mp.insert(10,13);
    mp.insert(9,20);
    mp.insert(29,30);
    mp.erase(9);
    cout<<mp[10]<<endl;
    cout<<mp.find(29)<<endl;
    mp.erase(10);
    mp[29]+=40;
    int a=1234.546;
}
/**
 * @brief Count no. of distinct elements in every sub-array of size k
 * 
 */
void problem()
{
    unordered_map<int,int>mp;
    int n,k,count=0;
    cin>>n>>k;
    int arr[n];
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    //initial window
    for(int i=0;i<k;i++)
    {
        if(!mp.find(arr[i]))
        {
            mp.insert(arr[i],1);
            count++;
        }
        else
            mp[arr[i]]+=1;
    }
    cout<<count;
    for(int i=k;i<n;i++)
    {
        if(mp[arr[i-k]]==1)
        {
            count--;
            mp.erase(arr[i-k]);
        }
        else
            mp[arr[i-k]]-=1;
        if(!mp.find(arr[i]))
        {
            count++;
            mp.insert(arr[i],1);
        }
        else
        {
            mp[arr[i]]+=1;
        }
        cout<<" "<<count;
    }
}
int main()
{
    //testcases();
    problem();
    return 0;
}