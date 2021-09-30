#include<iostream>
#include<sstream>
using namespace std;
/**
 * @brief Hash Map with O(1) complexity uses Chaining
 * 
 * @tparam T key value <class/typename>
 * @tparam V Value corresponding to key <class/typename>
 */
template <typename T,class V>
class unordered_map
{
    const static int MAX_BUCKET_SIZE=5;
    class Node
    {
        T key;
        V value;
        Node* right;
        public:
        Node(T key,V value)
        {
            this->key=key;
            this->value=value;
            right=NULL;
        }
    };
    //util functions:
    Node *buckets[MAX_BUCKET_SIZE];
    int  inline size()
    {
        return MAX_BUCKET_SIZE;
    }
    long long hash_function(T key)
    {

    }
    int hash(T key)
    {
        long long hashed_value=hash_function(key);
        return
    }
    public:
    unordered_map()
    {

    }
    void insert(T key, V value)
    {

    }
    void erase(T key)
    {

    }
    bool find(T key)
    {

    }
    V operator [](T key)
    {

    }
};
void testcases()
{
    unordered_map<float,float>mp;
    int a=1234.546;
    cout<<to_string(a)<<endl;
}
/**
 * @brief Count no. of distinct elements in every sub-array of size k
 * 
 */
void problem()
{

}
int main()
{
    testcases();
    return 0;
}