/**
 * @file Q3.cpp
 * @author Soumodipta Bose
 * @brief Trie Implementation
 * @version 0.1
 * @date 2021-11-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <string>
using namespace std;
#define LONG long long int
LONG binary_expo(LONG x, LONG n) // x^n
{
    LONG res = 1;
    // Traverse all the bits of the number
    while (n > 0)
    {
        if (n & 1) //if bit is set
            res = (res * x);
        x = (x * x);
        n >>= 1;
    }
    return res;
}
/**
 * @brief Node for binary Trie implementation
 * 
 */
class node
{
public:
    node *child[2] = {};
    int frequency;
    bool is_end;
    node()
    {
        frequency = 0;
        is_end = false;
    }
};
class Binarytrie
{
    int number_of_elements;
    node *root;

public:
    Binarytrie()
    {
        root = new node();
        number_of_elements = 0;
    }
    node *get_root()
    {
        return root;
    }
    void insert_word(string word)
    {
        node *current = root;
        for (int i = 0; i < word.length(); i++)
        {
            int index = word[i] - '0';
            if (current->child[index] == NULL)
            {
                current->child[index] = new node();
            }
            current = current->child[index];
        }
        current->frequency++;
        current->is_end = true;
        number_of_elements++;
    }
    int flip(char c)
    {
        if (c - '0')
            return 0;
        else
            return 1;
    }
    LONG max_xor_finder(string word)
    {
        int exponent = word.length() - 1;
        LONG sol = 0;
        node *current = get_root();
        for (auto bit : word)
        {
            int next_pos = flip(bit);
            if (current->child[next_pos] != NULL)
            {
                current = current->child[next_pos];
                sol += binary_expo(2, exponent);
            }
            else
            {
                current = current->child[1 - next_pos];
            }
            exponent--;
        }
        return sol;
    }
};
class Converter
{
    int max_bits;

public:
    Converter()
    {
        max_bits = 50;
    }
    Converter(int max_bits)
    {
        this->max_bits = max_bits;
    }
    char get_last_bit(LONG a)
    {
        if (a & 1)
            return '1';
        else
            return '0';
    }
    string normalizer(string bit_string)
    {
        int norm = max_bits - bit_string.length();
        if (norm > 0)
            bit_string.insert(0, norm, '0');
        return bit_string;
    }
    string binary_string(LONG number)
    {
        string binary = "";
        while (number)
        {
            binary.insert(0, 1, get_last_bit(number));
            number >>= 1;
        }
        binary = normalizer(binary);
        return binary;
    }
};
/**
 * @brief Find maximum of xor with given number and a number from the given list
 * 
 */
void solve()
{
    Binarytrie bin = Binarytrie();
    Converter con = Converter();
    int elements, queries;
    cin >> elements;
    for (int i = 0; i < elements; i++)
    {
        LONG number;
        cin >> number;
        bin.insert_word(con.binary_string(number));
    }
    cin >> queries;
    while (queries--)
    {
        LONG number;
        cin >> number;
        cout << bin.max_xor_finder(con.binary_string(number)) << endl;
    }
}
void test()
{
    Converter c = Converter(5);
    cout << c.binary_string(12) << endl;
    cout << c.binary_string(23) << endl;
}
int main()
{
    solve();
    return 0;
}