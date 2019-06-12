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

    vector<int> &topo()
    {
        return reverse_post;
    }
};

int main()
{
    vector<vector<int>> graph{{{1, 2, 5}, {4}, {}, {2, 4, 5, 6}, {}, {2}, {0, 4}}};
    auto topo = TopoSort(graph);
    for (auto const &v : topo.topo())
        printf("%d ", v);
    return 0;
}