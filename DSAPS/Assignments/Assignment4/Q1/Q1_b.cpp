/**
 * @file Q1.cpp
 * @author Soumodipta Bose
 * @brief Construction of suffix array
 * @version 0.1
 * @date 2021-11-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
class container
{
public:
    container() {}
    container(int rank, int next_rank)
    {
        this->rank = rank;
        this->next_rank = next_rank;
    }
    int rank;
    int next_rank;
};
bool operator==(const container &x, const container &t)
{
    if (x.rank == t.rank && x.next_rank == t.next_rank)
    {
        return true;
    }
    else
        return false;
}
class suffix_node
{
public:
    int index;
    string suffix;
    int rank;
    int next_rank;
};
bool compare(suffix_node a, suffix_node b)
{
    if (a.rank < b.rank)
        return true;
    else if (a.rank == b.rank && a.next_rank < b.next_rank)
        return true;
    return false;
}
class suffix_array
{

public:
    vector<suffix_node> array;
    suffix_array() {}
    suffix_array(string s)
    {
        create_suffix_array(s);
    }
    void print_suffix_array()
    {
        for (int i = 0; i < array.size(); i++)
        {
            cout << array[i].index << "\t" << array[i].rank << "\t" << array[i].next_rank << "\t" << array[i].suffix << endl;
        }
        cout << endl;
    }
    void init(string &s)
    {
        array.clear();
        for (int i = 0; i < s.size(); i++)
        {
            string temp = s.substr(i, s.size());
            suffix_node new_node = suffix_node();
            new_node.suffix = temp;
            new_node.index = i;
            new_node.rank = temp[0];
            new_node.next_rank = (temp.size() == 1) ? -1 : temp[1];
            array.push_back(new_node);
        }
        sort(array.begin(), array.end(), compare);
    }
    void create_suffix_array(string s)
    {
        init(s);
        print_suffix_array();
        for (int iter = 4; iter < array.size(); iter *= 2)
        {
            int init_rank = 0;
            container prev = container(array[0].rank, array[0].next_rank);
            array[0].rank = init_rank;
            int index_array[array.size()];
            index_array[array[0].index] = 0;
            for (int i = 1; i < array.size(); i++)
            {
                container current = container(array[i].rank, array[i].next_rank);
                index_array[array[i].index] = i;
                if (current == prev)
                {
                    array[i].rank = init_rank;
                }
                else
                {
                    prev = current;
                    init_rank = init_rank + 1;
                    array[i].rank = init_rank;
                }
            }
            for (int i = 0; i < array.size(); i++)
            {
                int idx = array[i].index + iter / 2;
                if (idx >= array.size())
                {
                    array[i].next_rank = -1;
                }
                else
                {
                    array[i].next_rank = array[index_array[idx]].rank;
                }
            }
            sort(array.begin(), array.end(), compare);
        }
        print_suffix_array();
    }
    int size()
    {
        return array.size();
    }
};
int main()
{
    string word;
    cin >> word;
    suffix_array n = suffix_array();
    n.create_suffix_array(word);
    return 0;
}