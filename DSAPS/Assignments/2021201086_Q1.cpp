#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
class node
{
    public:
    node *child[26]={};
    bool is_end;
    node()
    {
        is_end=false;
    }
};
class dictionary
{
    //Following are the apis of trie
    node *root=new node();
    int number_of_words;
    public:
    dictionary()
    {
        number_of_words=0;
    }
    void insert_word(string word);
    bool spell_check(string word);
    int get_word_count();

};
int dictionary::get_word_count()
{
    return number_of_words;
}
void dictionary::insert_word(string word)
{
    node *current=root;
    for(int i=0;i<word.length();i++)
    {
        int index=word[i]-'a';
        if(current->child[index]==NULL)
        {
            current->child[index]=new node();
        }
        current=current->child[index];
    }
    current->is_end=true;//end of word reached
}
bool dictionary::spell_check(string word)
{
    node *current=root;
    
}
/**
 * First line will contain number of words in dictionary n
 * Input the words
 */