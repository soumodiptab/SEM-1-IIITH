#include<iostream>
using namespace std;
class node
{
    public:
    string word;
    bool is_end;
    node* child[26]={NULL};
    node()
    {
        is_end=false;
        word="";
    }
};
class dictionary
{
    int number_of_words=0;
    node* root=new node();
    void traverse(node * current)
    {
        if(current->is_end)
        {
            cout<<current->word<<" ";
        }
        for(int i=0;i<26;i++)
        {
            if(current->child[i]!=NULL)
            {
                traverse(current->child[i]);
            }
        }
    }
    public:
    node* get_root()
    {
        return root;
    }
    void insert_word(string word)
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
    void print_words()
    {
        traverse(root);
    }
};
class grid
{
    int row;
    int col;
    char content[100][100];
    int movement[2][4]={{-1,0,1,0},{0,-1,0,1}};
    public:
    grid(int row,int col)
    {
        this->row=row;
        this->col=col;
    }
    bool index_check(int i,int j)
    {
        if(i<0 || i>=row)
            return false;
        if(j<0 || j>=col)
            return false;
        return true;
    }
    char get(int i,int j)
    {
        return content[i][j];
    }
    void set(int i,int j,char value)
    {
        content[i][j]=value;
    }
    /**
     * @brief Will print the state of the grid
     * 
     */
    void state()
    {
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<col;j++)
            {
                cout<<content[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    void traverse_grid(int i,int j, node *current,dictionary &sol)
    {
        int index=get(i,j)-'a';//reduce to get(i,j) normalize later
        //base condition
        if(!index_check(i,j) || get(i,j)=='#' || current->child[index]==NULL )
        {
            return;
        }
        current=current->child[index];
        if(current->is_end && !current->word.empty())
        {
            sol.insert_word(current->word);
            current->word.clear();
        }
        char original=get(i,j);
        set(i,j,'#');
        for(int k=0;k<4;k++)
        {
            traverse_grid(i+movement[0][k],j+movement[1][k],current,sol);
        }
        set(i,j,original);
    }
    void solve(int x,string* word_list)
    {
        dictionary input_words,output_words;
        for(int i=0;i<x;i++)
        {
            input_words.insert_word(word_list[i]);
        }
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<col;j++)
            {
                traverse_grid(i,j,input_words.get_root(),output_words);
            }
        }
        output_words.print_words();
        cout<<endl;
    }
};
void driver()
{
    int row,col;
    cin>>row>>col;
    grid g=grid(row,col);
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            char temp;
            cin>>temp;
            g.set(i,j,temp);
        }
    }
    int x;
    cin>>x;
    string word_list[x];
    for(int i=0;i<x;i++)
    {
        cin>>word_list[i];
    }
    g.solve(x,word_list);
}
int main()
{
    freopen("input_3.txt", "r", stdin);// REMOVE THIS after testing gets completed.
    driver();
    return 0;
}