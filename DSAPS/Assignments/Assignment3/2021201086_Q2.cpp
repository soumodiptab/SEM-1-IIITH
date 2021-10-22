#include <iostream>
#include <limits>
#include <vector>
using namespace std;
class tired_afk
{
    int number;
    vector<tired_afk *> children;
    tired_afk(int number)
    {
        this->number = number;
        children = vector<tired_afk *>(number);
    }
};

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
void reverse(vector<int> &array)
{
    int first = 0;
    int last = array.size() - 1;
    while (first < last)
    {
        swap(array[first], array[last]);
        first++;
        last--;
    }
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
    vector<vector<int>> path_tracer(vector<vector<int>> &parent, int index)
    {
        vector<vector<int>> paths;
        if (index == -1)
        {
            return paths;
        }
        for (auto item : parent[index])
        {
            vector<vector<int>> returned_paths = path_tracer(parent, item);
            if (returned_paths.empty())
            {
                vector<int> path;
                path.push_back(index);
                paths.push_back(path);
            }
            else
            {
                for (auto p : returned_paths)
                {
                    p.push_back(index);
                    paths.push_back(p);
                }
            }
        }
        return paths;
    }
    vector<int> select_best_path(vector<vector<int>> &paths)
    {
        vector<int> min_path = paths[0];
        for (int i = 1; i < paths.size(); i++)
        {
            for (int j = 0; j < (min_path.size()) && (j < paths[i].size()); j++)
            {
                if (paths[i][j] < min_path[j])
                {
                    min_path = paths[i];
                    break;
                }
            }
        }
        return min_path;
    }
    vector<vector<int>> shortest_path(int source)
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
        return parent;
    }
    void dijkstra_destination(int destination)
    {
        vector<vector<int>> parent = shortest_path(destination);
        vector<vector<int>> all_node_paths;
        for (int i = 0; i < nodes; i++)
        {
            vector<vector<int>> all_paths = path_tracer(parent, i);
            for (auto &p : all_paths)
            {
                reverse(p);
            }
            vector<int> best = select_best_path(all_paths);
            all_node_paths.push_back(best);
        }
        cout << "hello";
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
    g.dijkstra_destination(3);
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
    g1.dijkstra_destination(0);
}
int main()
{
    testcases();
}