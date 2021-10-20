#include <iostream>
#include <limits>
#include <vector>
#include <queue>
using namespace std;
class priorityqueue
{
    vector<pair<int,int>> keys;

public:
    priorityqueue()
    {
        ;
    }
    int top();
    void pop();
    void insert();
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
        weights[u].push_back(make_pair(weight,v));
        weights[v].push_back(make_pair(weight,u));
        edges++;
    }
    void shortest_path(int source)
    {
        vector<bool>visited(nodes,false);
        vector<int>distance(nodes,numeric_limits<int>::max());
        distance[source]=0;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > pq;
        pq.push(make_pair(0,source));
        while(!pq.empty())
        {
            pair<int,int>selected=pq.top();
            pq.pop();
            //iterate over all adjacent edges
            for(auto edge: weights[selected.second])
            {
                //first- weight second- adjacent vertex
                if(distance[selected.second]<distance[edge.second]+edge.first)
                {
                    distance[selected.second]=distance[edge.second]+edge.first;
                    pq.push()
                }
                
            }
        }
    }
    void k_shortest_paths()
    {

    }
};
void testcases()
{
    graph g(5);
    g.add_edge(0, 1, 2);
    g.add_edge(0, 3, 4);
    g.add_edge(1, 2, 3);
    g.shortest_path();
}
int main()
{
    testcases();
}