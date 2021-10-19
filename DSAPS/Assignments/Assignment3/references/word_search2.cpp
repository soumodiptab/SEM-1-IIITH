#include<bits/stdc++.h>
using namespace std;
class node
{
    public:
    node *child[26]={NULL};
    int count;
    string word="";
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
    void suggest_words(string prefix,node *current,vector<string>&sol);
    public:
    dictionary()
    {
        number_of_words=0;
    }
    node* get_root();
    void insert_word(string word);
    bool spell_check(string word);
    int get_word_count();
    vector<string> autocomplete(string query);
    string autocorrect(string word);

};
node* dictionary::get_root()
{
    return root;
}
int dictionary::get_word_count()
{
    return number_of_words;
}
/**
 * @brief Inserts the word into the dictionary
 * 
 * @param word 
 */
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
    current->is_end=true;
    current->word=word;
    number_of_words++;
}
class Solution {
    int rows,cols;
public:
    void solve(int i,int j,vector<vector<char>>& board,node* current,vector<string>&sol)
    {
        int index=board[i][j]-'a';
        if(board[i][j]=='$' || current->child[index]==NULL)
        {
            return;
        }
        char cached_char=board[i][j];
        current=current->child[index];
        board[i][j]='$';
        if(current->is_end && !current->word.empty())
        {
            sol.push_back(current->word);
            current->word.clear();
        }
        //up
        if(i>0)
            solve(i-1,j,board,current,sol);
        //left
        if(j>0)
            solve(i,j-1,board,current,sol);
        //down
        if(i<rows-1)
            solve(i+1,j,board,current,sol);
        //right
        if(j<cols-1)
            solve(i,j+1,board,current,sol);
        board[i][j]=cached_char;
        
    }
    vector<string> findWords(vector<vector<char>>& board,vector<string>& words) {
        vector<string>solution;
        rows=board.size();
        cols=board[0].size();
        dictionary dict=dictionary();
        for(auto w : words)
        {
            dict.insert_word(w);
        }
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
            {
                solve(i,j,board,dict.get_root(),solution);
            }
        }
        return solution;
    }
};