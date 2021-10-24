#include <bits/stdc++.h>
using namespace std;
class node
{
public:
    string word;
    bool is_end;
    node *child[26] = {NULL};
    node()
    {
        is_end = false;
        word = "";
    }
};
class dictionary
{
    int number_of_words = 0;
    node *root = new node();
    vector<string> final_words;
    void traverse(node *current)
    {
        if (current->is_end)
        {
            final_words.push_back(current->word);
        }
        for (int i = 0; i < 26; i++)
        {
            if (current->child[i] != NULL)
            {
                traverse(current->child[i]);
            }
        }
    }

public:
    node *get_root()
    {
        return root;
    }
    void insert_word(string word)
    {
        node *current = root;
        for (int i = 0; i < word.length(); i++)
        {
            int index = word[i] - 'a';
            if (current->child[index] == NULL)
            {
                current->child[index] = new node();
            }
            current = current->child[index];
        }
        current->is_end = true;
        current->word = word;
        number_of_words++;
    }
    vector<string> print_words()
    {
        traverse(root);
        return final_words;
    }
};
class grid
{
    int row;
    int col;
    char **content;
    int movement[2][4] = {{-1, 0, 1, 0}, {0, -1, 0, 1}};

public:
    grid(int row, int col)
    {
        this->row = row;
        this->col = col;
        content = new char *[row];
        for (int i = 0; i < row; i++)
        {
            content[i] = new char[col];
        }
    }
    bool index_check(int i, int j)
    {
        if (i < 0 || i >= row)
            return false;
        if (j < 0 || j >= col)
            return false;
        return true;
    }
    char get(int i, int j)
    {
        return content[i][j];
    }
    void set(int i, int j, char value)
    {
        content[i][j] = value;
    }
    /**
     * @brief Will print the state of the grid
     * 
     */
    void state()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                cout << content[i][j] << " ";
            }
            cout << endl;
        }
    }
    void traverse_grid(int i, int j, node *current, dictionary &sol)
    {
        //base condition
        if (!index_check(i, j) || get(i, j) == '#' || current->child[get(i, j) - 'a'] == NULL)
        {
            return;
        }
        current = current->child[get(i, j) - 'a'];
        if (current->is_end && !current->word.empty())
        {
            sol.insert_word(current->word);
            current->word.clear();
        }
        char original = get(i, j);
        set(i, j, '#');
        for (int k = 0; k < 4; k++)
        {
            traverse_grid(i + movement[0][k], j + movement[1][k], current, sol);
        }
        set(i, j, original);
    }
    vector<string> solve(vector<string> word_list)
    {
        int x = word_list.size();
        dictionary input_words, output_words;
        for (int i = 0; i < x; i++)
        {
            input_words.insert_word(word_list[i]);
        }
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                traverse_grid(i, j, input_words.get_root(), output_words);
            }
        }
        return output_words.print_words();
    }
};
class Solution
{
public:
    vector<string> findWords(vector<vector<char>> &board, vector<string> &words)
    {
        int row, col;
        row = board.size();
        col = board[0].size();
        grid g = grid(row, col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                g.set(i, j, board[i][j]);
            }
        }
        return g.solve(words);
    }
};
int main()
{
    vector<vector<char>> b{{'o', 'a', 'a', 'n'}, {'e', 't', 'a', 'e'}, {'i', 'h', 'k', 'r'}, {'i', 'f', 'l', 'v'}};
    vector<string> st{"oath", "pea", "eat", "rain"};
    Solution s;
    vector<string> sol = s.findWords(b, st);
    sol[0];
}