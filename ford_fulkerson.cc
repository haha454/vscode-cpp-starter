#include "trace.hh"
#include <bits/stdc++.h>

using namespace std;

class Edge
{
private:
    const int v, w, cap;
    int f;

public:
    Edge(int v, int w, int cap) : v(v), w(w), cap(cap), f(0) {}

    int from() { return v; }
    int to() { return w; }
    int capacity() { return cap; }
    int flow() { return f; }
    int other(int vertex)
    {
        if (vertex == v)
            return w;
        else if (vertex == w)
            return v;
        else
            throw exception();
    }

    int residualCapacityTo(int vertex)
    {
        if (vertex == v)
            return f;
        else if (vertex == w)
            return cap - f;
        else
            throw exception();
    }
    void addResidualFlowTo(int vertex, double delta)
    {
        if (vertex == v)
            f -= delta;
        else if (vertex == w)
            f += delta;
        else
            throw exception();
    }
};

class FordFulkerson
{
private:
    int n, flow;
    vector<bool> marked;
    vector<pair<int, Edge *>> edgeTo;

    bool has_augmenting_path(vector<vector<Edge *>> &graph, int s, int t)
    {
        edgeTo.assign(n, {-1, nullptr});
        marked.assign(n, false);

        // breadth-first search
        queue<int> q;
        q.push(s);
        marked[s] = true;
        while (!q.empty() && !marked[t])
        {
            int v = q.front();
            q.pop();

            for (auto &e : graph[v])
            {
                int w = e->other(v);

                // if residual capacity from v to w
                if (e->residualCapacityTo(w) && !marked[w])
                {
                    edgeTo[w] = {v, e};
                    marked[w] = true;
                    q.push(w);
                }
            }
        }

        // is there an augmenting path?
        return marked[t];
    }

public:
    FordFulkerson(vector<vector<Edge *>> &&graph, int s, int t)
    {
        n = graph.size();
        flow = 0;
        while (has_augmenting_path(graph, s, t))
        {
            // compute bottleneck capacity
            int bottle = 1e9 + 7;
            for (int v = t; v != s; v = edgeTo[v].first)
            {
                bottle = min(bottle, edgeTo[v].second->residualCapacityTo(v));
            }

            // augment flow
            for (int v = t; v != s; v = edgeTo[v].first)
            {
                edgeTo[v].second->addResidualFlowTo(v, bottle);
            }

            flow += bottle;
        }
    }

    int get_flow()
    {
        return flow;
    }

    bool in_cut(int v)
    {
        return marked[v];
    }
};

int main()
{
    int n, w, cap, m;
    cin >> n;
    vector<vector<Edge *>> graph(n); // vertex vs. <the other vertex, capacity>
    for (int i = 0; i < n; i++)
    {
        cin >> m;
        while (m--)
        {
            cin >> w >> cap;
            auto edge = new Edge(i, w, cap);
            graph[i].push_back(edge);
            graph[w].push_back(edge);
        }
    }
    auto ff = FordFulkerson(move(graph), 0, n - 1);
    printf("%d\n", ff.get_flow());
    for (int i = 0; i < n; i++)
        if (ff.in_cut(i))
            printf("%d ", i);
    return 0;
}