#include "trace.hh"
#include <bits/stdc++.h>

const double PI = 4 * atan(1);
const int INF = 1e9 + 7;
using namespace std;

// given a directed graph, check if it has a directed cycle.
class DirectedCycle
{
private:
    vector<vector<int>> g;
    vector<bool> visited, visiting;
    int n;
    int cycle_v;

    int search(int v)
    {
        visiting[v] = true;
        for (auto const &vv : g[v])
        {
            if (visited[vv])
                continue;
            if (visiting[vv])
                return vv;
            auto candidate = search(vv);
            if (candidate != -1)
                return candidate;
        }
        visited[v] = true;
        return -1;
    }

public:
    DirectedCycle(vector<vector<int>> &graph)
    {
        g = graph;
        n = g.size();
        visited.assign(n, false);
        visiting.assign(n, false);
        for (int i = 0; i < n; i++)
            if (!visited[i])
            {
                auto candidate = search(i);
                if (candidate != -1)
                {
                    cycle_v = candidate;
                    return;
                }
            }
        cycle_v = -1;
    }

    int vertex_on_cycle()
    {
        return cycle_v;
    }
};

int main()
{
    vector<vector<int>> graph{{1}, {2}, {0, 3}, {}};
    auto cycle = DirectedCycle(graph);
    printf("%d", cycle.vertex_on_cycle());
    return 0;
}