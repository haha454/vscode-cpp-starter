#include "trace.hh"
#include <bits/stdc++.h>

using namespace std;

struct Edge
{
    int v, w;
    double weight;
    Edge(int v, int w, double weight) : v(v), w(w), weight(weight) {}
};

// assume every pair is connected directly or indirectly in a undirected graph
class Prim
{
private:
    vector<pair<int, int>> mst;

public:
    Prim(vector<Edge> &&edges)
    {
        unordered_map<int, vector<Edge>> v_edge_map;
        unordered_map<int, bool> marked;
        auto greater_edge_comp = [](const Edge &e, const Edge &v) {
            return e.weight > v.weight;
        };
        priority_queue<Edge, vector<Edge>, decltype(greater_edge_comp)> pq(greater_edge_comp);
        for (auto const &edge : edges)
        {
            v_edge_map[edge.v].push_back(edge);
            v_edge_map[edge.w].push_back(edge);
        }
        int first_vertex = edges.front().v;
        for (auto const &edge : v_edge_map[first_vertex])
            pq.push(edge);
        marked[first_vertex] = true;
        while (!pq.empty())
        {
            while (!pq.empty() && marked[pq.top().v] && marked[pq.top().w])
                pq.pop();
            if (pq.empty())
                return;
            int next_vertex = marked[pq.top().v] ? pq.top().w : pq.top().v;
            mst.emplace_back(pq.top().v, pq.top().w);
            for (auto const &edge : v_edge_map[next_vertex])
                if (!marked[edge.v] && !marked[edge.w])
                    pq.push(edge);
            marked[next_vertex] = true;
        }
    }

    vector<pair<int, int>> get_mst()
    {
        return mst;
    }
};

int main()
{
    vector<Edge> edges;
    int v, w;
    double weight;
    while (scanf("%d %d %lf", &v, &w, &weight) != EOF)
        edges.emplace_back(v, w, weight);
    auto prim = Prim(move(edges));
    for (auto const &e : prim.get_mst())
        printf("%d %d\n", e.first, e.second);
    return 0;
}