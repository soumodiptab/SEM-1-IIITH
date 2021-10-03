// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;



 // } Driver Code Ends

class unordered_mp
{
    const static int MAX_BUCKET_SIZE=100000;
    const int prime=31;
    class Node
    {
        public:
        int key;
        int value;
        Node* prev;
        Node* next;
        Node(int key,int value)
        {
            this->key=key;
            this->value=value;
            prev=NULL;
            next=NULL;
        }
    };
    //util functions:
    Node *buckets[MAX_BUCKET_SIZE]={NULL};
    string convert_to_String(int key)
    {
        ostringstream stream;
        stream << key;
        string converted_string=stream.str();
        return converted_string;
    }
    int hash_function(int key)
    {
        long long int hashed_value=0;
        string key_string=convert_to_String(key);
        long long int factor = 1;
        for (char letter : key_string)
        {
            hashed_value = (hashed_value + (letter * factor) % MAX_BUCKET_SIZE) % MAX_BUCKET_SIZE;
            factor = (factor * prime) % MAX_BUCKET_SIZE;
        }
        return hashed_value;
    }
    Node* find_node(int key)
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
    void insert(int key, int value)
    {
        Node *target=find_node(key);
        if(target!=NULL)
        {
            target->value=value;
            return;
        }
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
    void erase(int key)
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
    bool find(int key)
    {
        return (find_node(key)!=NULL)?true:false;
    }
    int& operator [](int key)
    {
        Node* temp=find_node(key);
        if(temp==NULL)
        {
            int val=0;
            insert(key,val);
            temp=find_node(key);
        }
        return temp->value;
    }
    /**
     * @brief Use this to check the location of hashed keys
     * 
     */
    void debug()
    {
        for(int i=1;i<40;i++)
        {
            cout<<i<<" "<<hash_function(i)<<endl;
        }
    }
    void display()
    {

    }
};

class Solution{
  public:
    vector <int> countDistinct (int arr[], int n, int k)
    {
        vector<int>sol;
        unordered_mp hm;

    // initialize distinct element count for current window
    int dist_count = 0;

    // Traverse the first window and store count
    // of every element in hash map
    for (int i = 0; i < k; i++) {
        if (hm[arr[i]] == 0) {
            dist_count++;
        }
        hm.insert(arr[i],hm[arr[i]]+1);
    }

    // Print count of first window
    sol.push_back(dist_count);

    // Traverse through the remaining array
    for (int i = k; i < n; i++) {
        // Remove first element of previous window
        // If there was only one occurrence, then reduce distinct count.
        if (hm[arr[i - k]] == 1) {
            dist_count--;
        }
        // reduce count of the removed element
        hm.insert(arr[i-k],hm[arr[i-k]]-1);

        // Add new element of current window
        // If this element appears first time,
        // increment distinct element count

        if (hm[arr[i]] == 0) {
            dist_count++;
        }
        hm.insert(arr[i],hm[arr[i]]+1);

        // Print count of current window
        sol.push_back(dist_count);
    }
        return sol;
    }
};

// { Driver Code Starts.
int main()
{
    int t;
    cin >> t;
    while (t--)
    {

        int n, k;
        cin >> n >> k;
        int a[n];
        for (int i = 0; i < n; i++) 
        	cin >> a[i];
        Solution obj;
        vector <int> result = obj.countDistinct(a, n, k);
        for (int i : result) 
        	cout << i << " ";
        cout << endl;
    }
    return 0;
}  // } Driver Code Ends