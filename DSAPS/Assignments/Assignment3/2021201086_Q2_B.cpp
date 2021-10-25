#include <iostream>
#include <limits>
#include <vector>
#include <stack>
#include <sstream>
#include <algorithm>
using namespace std;
bool lexo_compare(const pair<int, string> &a, const pair<int, string> &b)
{
    if (a.first != b.first)
        return (a.first < b.first);
    return (a.second.compare(b.second) < 0);
}
class graph
{
    int nodes;
    int edges;
    /**
     * Adjaceny list representation:
     * 
     */
    vector<vector<pair<int, int>>> weights;
    vector<pair<int, string>> weight_paths;

public:
    graph(int nodes)
    {
        this->nodes = nodes;
        this->edges = 0;
        weights = vector<vector<pair<int, int>>>(nodes);
    }
    void add_edge(int u, int v, int weight)
    {
        weights[u].push_back(make_pair(weight, v));
        weights[v].push_back(make_pair(weight, u));
        edges++;
    }
    void print_k_paths(int k)
    {
        if (k >= weight_paths.size())
        {
            k = weight_paths.size();
        }
        for (int i = 0; i < k; i++)
        {
            cout << weight_paths[i].second << endl;
        }
    }
    char to_character(int number)
    {
        stringstream tmp;
        tmp << number;
        char ch;
        tmp >> ch;
        return ch;
    }
    void dfs(int source, int destination, vector<bool> visited, string path, int weight)
    {
        if (visited[source])
            return;
        visited[source] = true;
        if (source == destination)
        {
            weight_paths.push_back(make_pair(weight, path));
            return;
        }
        for (auto i : weights[source])
        {
            path.push_back(' ');
            path.push_back(to_character(i.second));
            dfs(i.second, destination, visited, path, weight + i.first);
            path.pop_back();
            path.pop_back();
        }
    }
    bool equals(string a, string b)
    {
        reverse(b.begin(), b.end());
        if (a.compare(b) == 0)
            return true;
        return false;
    }
    void cleanup()
    {
        // 0 - remove 1-accept -1:unresolved
        vector<int> marker(weight_paths.size(), -1);
        for (int i = 0; i < weight_paths.size() - 1; i++)
        {
            if (marker[i] == 1 || marker[i] == 0)
            {
                continue;
            }
            for (int j = i + 1; (j < weight_paths.size() && (weight_paths[i].first == weight_paths[j].first)); j++)
            {
                string a = weight_paths[i].second;
                string b = weight_paths[j].second;
                if (equals(a, b))
                {
                    if (a.compare(b) < 0)
                    {
                        marker[i] = 1;
                        marker[j] = 0;
                    }
                    else
                    {
                        marker[i] = 0;
                        marker[j] = 1;
                    }
                }
            }
        }
        vector<pair<int, string>> final;
        for (int i = 0; i < weight_paths.size(); i++)
        {
            if (marker[i] != 0)
                final.push_back(weight_paths[i]);
        }
        weight_paths = final;
    }
    void get_all_paths()
    {
        weight_paths.clear();
        for (int source = 0; source < nodes; source++)
        {
            for (int destination = 0; destination < nodes; destination++)
            {
                if (source == destination)
                    continue;
                vector<bool> visited(nodes, false);
                string path = "";
                path.push_back(to_character(source));
                dfs(source, destination, visited, path, 0);
            }
        }
        sort(weight_paths.begin(), weight_paths.end(), lexo_compare);
        cleanup();
    }
};
void kth_shortest_paths_solver()
{
    int vertex, edges, k;
    cin >> vertex >> edges;
    int a, b, c, dest;
    graph g(vertex);
    for (int i = 1; i <= edges; i++)
    {
        cin >> a >> b >> c;
        g.add_edge(a, b, c);
    }
    cin >> k;
    g.get_all_paths();
    g.print_k_paths(k);
}
int main()
{
    //freopen("input_2.txt", "r", stdin);
    kth_shortest_paths_solver();
}