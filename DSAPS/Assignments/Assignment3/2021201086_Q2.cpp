#include <iostream>
#include <limits>
#include <vector>
using namespace std;
class priority_queue
{
    vector<pair<int, int>> key_value;
    int max = -1;
    int parent(int index)
    {
        return (index - 1) / 2;
    }
    int left_child(int index)
    {
        return ((2 * index) + 1);
    }
    int right_child(int index)
    {
        return ((2 * index) + 2);
    }
    void max_heapify(int index)
    {
        int smallest = index;
        int l = left_child(index);
        int r = right_child(index);
        if (l <= max && key_value[l] < key_value[smallest])
        {
            smallest = l;
        }
        if (r <= max && key_value[r] < key_value[smallest])
        {
            smallest = r;
        }
        if (smallest != index)
        {
            key_value[index].swap(key_value[smallest]);
            max_heapify(smallest);
        }
    }
    void fix_heap_up(int index)
    {
        while (index > 0 && key_value[parent(index)] > key_value[index])
        {
            key_value[parent(index)].swap(key_value[index]);
            index = parent(index);
        }
    }
    void insert_key(pair<int, int> k_v)
    {
        max++;
        key_value.push_back(k_v);
        fix_heap_up(max);
    }
    void delete_min()
    {
        if (max == -1)
            return;
        if (max > 0)
        {
            key_value[0].swap(key_value[max]);
            max--;
            key_value.pop_back();
            max_heapify(0);
        }
        else
        {
            max--;
            key_value.pop_back();
        }
    }
    //-----------------------------------------------------------------------
public:
    pair<int, int> top()
    {
        return key_value[0];
    }
    void push(pair<int, int> ele)
    {
        insert_key(ele);
    }
    void pop()
    {
        delete_min();
    }
    bool empty()
    {
        if (max == -1)
        {
            return true;
        }
        return false;
    }
};
class graph
{
    int nodes;
    int edges;
    /**
     * Adjaceny list representation:
     * 
     */
    vector<vector<pair<int, int>>> weights;

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
    /**
     * @brief create all possible paths
     * 
     */
    vector<string> path_tracer(vector<vector<int>> &parent, int index)
    {
        vector<string>paths;
        if(index==-1)
        {
            return paths;
        }
        string path = "";
        for (auto item : parent[index])
        {
                path = to_string(item) + " " + path;
            }
            index = parent[index][0];
        cout << path;
    }
    void shortest_path(int source)
    {
        vector<bool> visited(nodes, false);
        vector<int> distance(nodes, numeric_limits<int>::max());
        vector<vector<int>> parent = vector<vector<int>>(nodes);
        parent[source].push_back(-1);
        distance[source] = 0;
        priority_queue pq = priority_queue();
        pq.push(make_pair(0, source));
        while (!pq.empty())
        {
            pair<int, int> selected = pq.top();
            pq.pop();
            if (visited[selected.second])
                continue;
            //iterate over all adjacent edges
            visited[selected.second] = true;
            for (auto edge : weights[selected.second])
            {
                //first- weight second- adjacent vertex
                if (distance[selected.second] + edge.first < distance[edge.second])
                {
                    parent[edge.second].clear();
                    parent[edge.second].push_back(selected.second);
                    distance[edge.second] = distance[selected.second] + edge.first;
                    pq.push(make_pair(distance[edge.second], edge.second));
                }
                else if (distance[selected.second] + edge.first == distance[edge.second])
                {
                    parent[edge.second].push_back(selected.second);
                }
            }
        }
        path_tracer(parent, 3);
    }
    void k_shortest_paths()
    {
    }
};
void testcases()
{
    graph g(4);
    g.add_edge(0, 1, 1);
    g.add_edge(1, 3, 2);
    g.add_edge(0, 3, 3);
    g.add_edge(0, 2, 2);
    g.add_edge(2, 3, 1);
    g.shortest_path(0);
    cout << endl;
    graph g1(7);
    g1.add_edge(0, 1, 2);
    g1.add_edge(1, 2, 1);
    g1.add_edge(1, 3, 3);
    g1.add_edge(0, 5, 5);
    g1.add_edge(5, 6, 1);
    g1.add_edge(2, 6, 2);
    g1.add_edge(4, 6, 2);
    g1.add_edge(3, 4, 6);
    g1.shortest_path(0);
}
int main()
{
    testcases();
}