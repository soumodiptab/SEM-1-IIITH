#include<iostream>
#include<string>
#include<map>
#include<unordered_set>
using namespace std;
template <typename T,typename T2>
class LFU{
    int cap,size;
    map<int,int>key_value;
    map<int,int>key_freq;
    map<int,unordered_set<int>>freq_list;
    public:
    LFU(int capacity)
    {
        size=0;
        cap=capacity;
    }
    int get(int key)
    {

    }
    void put(int key,int val)
    {
        if(cap<=0)
            return;
        if(key_value.find(key)!=key_value.end())
        {
            key_value[key]=val;
            int count=key_freq[key];
            key_freq[key]++;
            freq_list[count].erase(key);
            if(freq_list[count].size()==0)
                freq_list.erase(count);
            freq_list[count+1].insert(key);
        }
        else
        {
            if(size==cap)
            {
                int target=*(freq_list.begin()->second.begin());
                freq_list.begin()->second.erase(target);
                key_value.erase(target);
                key_freq.erase(target);
            }
            else
            {
                size++;
            }
            key_value[key]=val;
            key_freq[key]=1;
            freq_list[1].insert(key);
        }
        
    }

};
int main()
{

    return 0;
}