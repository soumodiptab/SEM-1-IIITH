/**
 * @file Q1.cpp
 * @author Soumodipta Bose
 * @brief Find length of the Longest substring of occurence greater than equals k
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
    string word;
    vector<suffix_node> array;
    suffix_array() {}
    void print_suffix_array()
    {
        for (int i = 0; i < array.size(); i++)
        {
            cout << array[i].index << "\t" << array[i].rank << "\t" << array[i].next_rank << "\t" << word.substr(array[i].index, word.size() - array[i].index) << endl;
        }
        cout << endl;
    }
    void init(string &s)
    {
        array.clear();
        word = s;
        for (int i = 0; i < word.size(); i++)
        {
            string temp = word.substr(i, word.size());
            suffix_node new_node = suffix_node();
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
        //print_suffix_array();
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
        //print_suffix_array();
    }
    int size()
    {
        return array.size();
    }
    string get_suffix(int i)
    {
        return word.substr(array[i].index, word.size());
    }
};
string prefix_matcher(string a, string b)
{
    int i = 0;
    string lcp = "";
    while (i < a.size() && i < b.size() && a[i] == b[i])
    {
        lcp.push_back(a[i++]);
    }
    return lcp;
}
void sol(string word, int k)
{
    suffix_array suf = suffix_array();
    suf.create_suffix_array(word);
    string max_lcp = "";
    suf.get_suffix(0);

    for (int i = 0; i <= suf.size() - k; i++) // Run from i = 0 to i= length - k
    {
        //  check if prefix exists at k-1th position
        string lcp = prefix_matcher(suf.get_suffix(i), suf.get_suffix(i + k - 1));
        if (lcp.size() > max_lcp.size())
        {
            max_lcp = lcp;
        }
    }
    int length = -1;
    if (!max_lcp.empty())
        length = max_lcp.size();
    cout << length << endl;
}
int main()
{
    string word;
    int k;
    cin >> word >> k;
    char c = word[0];
    bool flag = true;
    for (int i = 1; i < word.size(); i++)
    {
        if (c != word[i])
        {
            flag = false;
            break;
        }
    }
    if (flag)
    {
        cout << (word.size() - k + 1) << endl;
        return 0;
    }
    sol(word, k);
    return 0;
}