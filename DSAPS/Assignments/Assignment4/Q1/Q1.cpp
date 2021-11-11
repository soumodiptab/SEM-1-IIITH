/**
 * @file Q1.cpp
 * @author your name (you@domain.com)
 * @brief 
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
    else if (a.rank == b.rank && a.next_rank <= a.next_rank)
        return true;
    return false;
}
class suffix_array
{
    vector<suffix_node> array;

public:
    suffix_array() {}
    void create_suffix_array(string s)
    {
        s = s.append(s);
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
        cout << "hello";

        
    }
};

void sol(string s)
{
}
int main()
{
    string word;
    cin >> word;
    suffix_array n = suffix_array();
    n.create_suffix_array(word);
    return 0;
}