#include "trace.hh"
#include <bits/stdc++.h>

const double PI = 4 * atan(1);
const int INF = 1e9 + 7;
using namespace std;

// given a directed graph, assume graph has no directed cycle, find its topological order.
class TopoSort
{
private:
    vector<vector<int>> g;
    vector<bool> marked;
    vector<int> reverse_post;
    int n;

    void search(int v)
    {
        marked[v] = true;
        for (auto const &vv : g[v])
            if (!marked[vv])
                search(vv);
        reverse_post.push_back(v);
    }

public:
    TopoSort(vector<vector<int>> &graph)
    {
        g = graph;
        n = g.size();
        marked.assign(n, false);
        for (int i = 0; i < n; i++)
            if (!marked[i])
                search(i);
        reverse(reverse_post.begin(), reverse_post.end());
    }

    const vector<int> &topo() const
    {
        return reverse_post;
    }
};

// strongly connected: there is both a directed path from v to w and a directed path from w to v
// strong componet: maximal subset of strongly-connected vertices
// Phase 1: run DFS on GR to compute reverse postorder.
// Phase 2: run DFS on G, considering vertices in order given by first DFS
class StrongComponent
{
private:
    vector<vector<int>> g;
    vector<bool> marked;
    vector<int> component;
    int component_count;
    int n;

    void search(int v, int component_num)
    {
        marked[v] = true;
        component[v] = component_num;
        for (auto const &vv : g[v])
            if (!marked[vv])
                search(vv, component_num);
    }

    vector<vector<int>> reverse_graph(vector<vector<int>> &graph)
    {
        vector<vector<int>> g(graph.size());

        for (unsigned int i = 0; i < graph.size(); i++)
        {
            for (auto const &v : graph[i])
                g[v].push_back(i);
        }
        return g;
    }

public:
    StrongComponent(vector<vector<int>> &graph)
    {
        auto rg = reverse_graph(graph);
        g = graph;
        n = g.size();
        marked.assign(n, false);
        component.resize(n);
        component_count = 0;
        auto topo = TopoSort(rg);
        const vector<int> &topo_order = topo.topo();
        for (auto const &v : topo_order)
            if (!marked[v])
                search(v, component_count++);
    }

    const vector<int> &get_component_id() const
    {
        return component;
    }

    const int &get_num_component() const
    {
        return component_count;
    }
};

int main()
{
    vector<vector<int>> graph{{2, 6}, {0}, {3, 4}, {2, 4}, {5, 6, 11}, {0, 3}, {7, 8}, {}, {6}, {6, 7, 12}, {9}, {9}, {10, 11}};
    auto scc = StrongComponent(graph);
    printf("there are %d scc.\n", scc.get_num_component());
    for (auto const &v : scc.get_component_id())
        printf("%d ", v);
    return 0;
}