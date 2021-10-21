#include <iostream>
#include <vector>
using namespace std;
class priority_queue
{
    vector<pair<int, int>> key_value;
    int max = -1;
    int parent(int index)
    {
        return (index - 1) / 2;
    }
    int left_child(int index)
    {
        return ((2 * index) + 1);
    }
    int right_child(int index)
    {
        return ((2 * index) + 2);
    }
    void max_heapify(int index)
    {
        int smallest = index;
        int l = left_child(index);
        int r = right_child(index);
        if (l <= max && key_value[l] < key_value[smallest])
        {
            smallest = l;
        }
        if (r <= max && key_value[r] < key_value[smallest])
        {
            smallest = r;
        }
        if (smallest != index)
        {
            key_value[index].swap(key_value[smallest]);
            max_heapify(smallest);
        }
    }
    void fix_heap_up(int index)
    {
        while (index > 0 && key_value[parent(index)] > key_value[index])
        {
            key_value[parent(index)].swap(key_value[index]);
            index = parent(index);
        }
    }
    void insert_key(pair<int, int> k_v)
    {
        max++;
        key_value.push_back(k_v);
        fix_heap_up(max);
    }
    void delete_min()
    {
        if (max == -1)
            return;
        if (max > 0)
        {
            key_value[0].swap(key_value[max]);
            max--;
            max_heapify(0);
        }
        key_value.pop_back();
    }
    //-----------------------------------------------------------------------
public:
    pair<int, int> top()
    {
        return key_value[0];
    }
    void push(pair<int, int> ele)
    {
        insert_key(ele);
    }
    void pop()
    {
        delete_min();
    }
    bool empty()
    {
        if (max == -1)
        {
            return true;
        }
        return false;
    }
};
int main()
{
    priority_queue pq = priority_queue();
    pq.push(make_pair(23, 1));
    pq.push(make_pair(12, 2));
    pq.push(make_pair(8, 3));
    pq.top();
    pq.pop();
    pq.push(make_pair(34, 4));
    pq.push(make_pair(8, 5));
    pq.push(make_pair(8, 6));
    pq.top();
    return 0;
}