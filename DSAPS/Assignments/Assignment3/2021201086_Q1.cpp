#include <iostream>
#include <vector>
using namespace std;
/**
 * @brief Trie node: is_end marks the end of word and child has all the pointers to different alphabets
 * 
 */
class node
{
public:
    node *child[26] = {};
    bool is_end;
    node()
    {
        is_end = false;
    }
};
class dictionary
{
    //Following are the apis of trie
    node *root = new node();
    int number_of_words;
    int min(int a, int b, int c);
    bool size_check(string a, string b);
    void suggest_words(string prefix, node *current, vector<string> &sol);
    void similar_words(string query, string prefix, node *current, vector<string> &sol);
    int get_edit_distance(string word_a, string word_b);

public:
    dictionary()
    {
        number_of_words = 0;
    }
    void insert_word(string word);
    node *find_node(string word);
    node *prefix_match(string word);
    bool spell_check(string word);
    int get_word_count();
    vector<string> get_all_words();
    vector<string> autocomplete(string query);
    vector<string> autocorrect(string word);
    void test()
    {
        cout << get_edit_distance("app", "apple") << endl;
        cout << get_edit_distance("dragon", "rem") << endl;
        cout << get_edit_distance("xcvy", "rem") << endl;
    }
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
    number_of_words++;
}
bool dictionary::spell_check(string word)
{
    node *target = find_node(word);
    if (target == NULL)
    {
        return false;
    }
    return target->is_end;
}
node *dictionary::find_node(string word)
{
    node *current = root;
    for (int i = 0; i < word.length(); i++)
    {
        int index = word[i] - 'a';
        if (current->child[index] == NULL)
            return NULL;
        current = current->child[index];
    }
    return current;
}
vector<string> dictionary::autocomplete(string query)
{
    //find target node first
    vector<string> suggestions;
    node *target;
    target = root;
    if (!query.empty())
        target = find_node(query);
    if (target == NULL)
        return suggestions; //empty - no suggestion
    suggest_words(query, target, suggestions);
    return suggestions; //Partial prefix match , provide all suggestions after that prefix
}
void dictionary::suggest_words(string prefix, node *current, vector<string> &sol)
{
    if (current->is_end)
    {
        sol.push_back(prefix);
    }
    for (int i = 0; i < 26; i++)
    {
        if (current->child[i] != NULL)
        {
            char ch = 'a' + i;
            prefix.push_back(ch);
            suggest_words(prefix, current->child[i], sol);
            prefix.pop_back();
        }
    }
}
int dictionary::min(int a, int b, int c)
{
    return std::min(a, std::min(b, c));
}
int dictionary::get_edit_distance(string word_a, string word_b)
{
    vector<vector<int>> cache(word_a.length() + 1, vector<int>(word_b.length() + 1, 0));
    for (int i = 0; i <= word_a.length(); i++)
    {
        for (int j = 0; j <= word_b.length(); j++)
        {
            if (i == 0)
            {
                cache[i][j] = j;
            }
            else if (j == 0)
            {
                cache[i][j] = i;
            }
            else if (word_a[i - 1] == word_b[j - 1]) //match
            {
                cache[i][j] = cache[i - 1][j - 1];
            }
            else
            {
                cache[i][j] = 1 + min(cache[i][j - 1], cache[i - 1][j - 1], cache[i - 1][j]);
            }
        }
    }
    return cache[word_a.length()][word_b.length()];
}

void dictionary::similar_words(string query, string prefix, node *current, vector<string> &sol)
{
    if (current->is_end && size_check(query, prefix) && get_edit_distance(query, prefix) <= 3)
    {
        sol.push_back(prefix);
    }
    for (int i = 0; i < 26; i++)
    {
        if (current->child[i] != NULL)
        {
            char ch = 'a' + i;
            prefix.push_back(ch);
            similar_words(query, prefix, current->child[i], sol);
            prefix.pop_back();
        }
    }
}
bool dictionary::size_check(string a, string b)
{
    int size = a.length() - b.length();
    if (abs(size) > 3)
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
    //Assumption: we print all words that are 3 edit distance away from the given word
    vector<string> sim_words;
    similar_words(word, "", root, sim_words);
    return sim_words;
}
/**
 * First line will contain number of words in dictionary n
 * Input the words
 */
void print_vector(vector<string> stream)
{
    cout << stream.size() << endl;
    for (auto s : stream)
    {
        cout << s << endl;
    }
}
void testcases()
{
    dictionary dict = dictionary();
    dict.insert_word("h");
    dict.insert_word("hello");
    dict.insert_word("hemlo");
    dict.insert_word("apple");
    dict.insert_word("app");
    dict.insert_word("dragon");
    dict.insert_word("herring");
    dict.insert_word("hem");
    dict.insert_word("hoshigawa");
    dict.insert_word("appl");
    cout << dict.spell_check("hemlo") << endl;
    cout << dict.spell_check("hem") << endl;
    cout << dict.spell_check("appl") << endl;
    vector<string> suggest = dict.autocomplete("dra");
    print_vector(suggest);
    cout << "------------------------------------" << endl;
    dict.test();
    vector<string> simlilar = dict.autocorrect("appl");
    print_vector(simlilar);
}
void test_case_medium()
{
    freopen("input_1.txt", "r", stdin);
    int words, option;
    string temp;
    cin >> words;
    dictionary dict = dictionary();
    for (int i = 0; i < words; i++)
    {
        cin >> temp;
        dict.insert_word(temp);
    }
    int testcases;
    cin >> testcases;
    while (testcases--)
    {
        cin >> option;
        cin >> temp;
        switch (option)
        {
        case 1:
            cout << dict.spell_check(temp) << endl;
            break;
        case 2:
            print_vector(dict.autocomplete(temp));
            break;
        case 3:
            print_vector(dict.autocorrect(temp));
            break;
        default:
            break;
        }
        cout << endl;
    }
}
void driver()
{
    int words, option;
    string temp;
    cin >> words;
    dictionary dict = dictionary();
    for (int i = 0; i < words; i++)
    {
        cin >> temp;
        dict.insert_word(temp);
    }
    cin >> option;
    cin >> temp;
    switch (option)
    {
    case 1:
        cout << dict.spell_check(temp) << endl;
        break;
    case 2:
        print_vector(dict.autocomplete(temp));
        break;
    case 3:
        print_vector(dict.autocorrect(temp));
        break;
    default:
        break;
    }
}
int main()
{
    //testcases();
    //test_case_medium();
    driver();
    return 0;
}