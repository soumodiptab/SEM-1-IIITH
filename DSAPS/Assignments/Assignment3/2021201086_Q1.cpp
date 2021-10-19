#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;
/**
 * @brief Trie node: is_end marks the end of word and child has all the pointers to different alphabets
 * 
 */
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
    int min(int a,int b,int c);
    bool size_check(string a,string b);
    void suggest_words(string prefix,node *current,vector<string>&sol);
    void similar_words(string query,string prefix,node *current,vector<string>&sol);
    int get_edit_distance(string word_a,string word_b);
    public:
    dictionary()
    {
        number_of_words=0;
    }
    void insert_word(string word);
    node* find_node(string word);
    bool spell_check(string word);
    int get_word_count();
    vector<string> get_all_words();
    vector<string> autocomplete(string query);
    vector<string> autocorrect(string word);

};
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
    number_of_words++;
}
bool dictionary::spell_check(string word)
{
    node* target=find_node(word);
    if(target==NULL)
        return false;
    return target->is_end;
}
node* dictionary::find_node(string word)
{
    node *current=root;
    for(int i=0;i<word.length();i++)
    {
        int index=word[i]-'a';
        if(current->child[index]==NULL)
            return NULL;
        current=current->child[index];
    }
    return current;
}
vector<string> dictionary::autocomplete(string query)
{
    //find target node first
    vector<string>suggestions;
    node *current=root;
    node *target=find_node(query);
    if(target==NULL)
        return suggestions;//empty - no suggestion
    suggest_words(query,target,suggestions);
    return suggestions;//Partial prefix match , provide all suggestions after that prefix
}
void dictionary::suggest_words(string prefix,node *current,vector<string>&sol)
{
    if(current->is_end)
    {
        sol.push_back(prefix);
    }
    for(int i=0;i<26;i++)
    {
        if(current->child[i]!=NULL)
        {
            char ch='a'+i;
            prefix.push_back(ch);
            suggest_words(prefix,current->child[i],sol);
            prefix.pop_back();
        }
    }
}
int dictionary::min(int a,int b,int c)
{
    return std::min(a,std::min(b,c));
}
int dictionary::get_edit_distance(string word_a,string word_b)
{
    int cache[word_a.length()+1][word_b.length()+1];
    for(int i=0;i<=word_a.length();i++)
    {
        for(int j=0;j<=word_b.length();j++)
        {
            if(i==0)
            {
                cache[i][j]=j;
            }
            else if(j==0)
            {
                cache[i][j]=i;
            }
            else if(word_a[i]==word_b[j])//match
            {
                cache[i][j]=cache[i-1][j-1];
            }
            else
            {
                cache[i][j]=min(cache[i][j-1],cache[i-1][j-1],cache[i-1][j]);
            }
        }
    }
    return cache[word_a.length()][word_b.length()];
}

void dictionary::similar_words(string query,string prefix,node *current,vector<string>&sol)
{
    if(current->is_end && size_check(query,prefix) && get_edit_distance(query,prefix)<=3)
    {
        sol.push_back(prefix);
    }
    for(int i=0;i<26;i++)
    {
        if(current->child[i]!=NULL)
        {
            char ch='a'+i;
            prefix.push_back(ch);
            similar_words(query,prefix,current->child[i],sol);
            prefix.pop_back();
        }
    }
}
bool size_check(string a,string b)
{
    int size=a.length()-b.length();
    if(abs(size)>3)
        return false;
    return true;
}
/**
 * @brief 
 * 
 * @param word 
 * @return string 
 */
vector<string> dictionary::autocorrect(string word)
{
    vector<string>sim_words;
    node *target=find_node(word);
    if(target!=NULL)
    {
        sim_words.push_back(word);
        return sim_words;
    }
    similar_words(word,"",root,sim_words);
    return sim_words;
}
/**
 * First line will contain number of words in dictionary n
 * Input the words
 */
void testcases()
{
    dictionary dict=dictionary();
    dict.insert_word("h");
    dict.insert_word("hello");
    dict.insert_word("hemlo");
    dict.insert_word("apple");
    dict.insert_word("app");
    dict.insert_word("dragon");
    dict.insert_word("herring");
    dict.insert_word("hoshigawa");
    cout<<dict.spell_check("hemlo")<<endl;
    cout<<dict.spell_check("hem")<<endl;
    cout<<dict.spell_check("appl")<<endl;
    dict.autocomplete("der");
}
int main()
{
    testcases();
    return 0;
}