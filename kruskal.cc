#include "trace.hh"
#include <bits/stdc++.h>

using namespace std;

struct Edge
{
    int v, w;
    double weight;
    Edge(int v, int w, double weight) : v(v), w(w), weight(weight) {}
};

class UF
{
private:
    unordered_map<int, int> root;
    unordered_map<int, int> rank;
    unordered_map<int, int> size;
    int num_combine;

public:
    UF() : num_combine(0)
    {
    }

    int find_root(int x)
    {
        if (root.find(x) == root.end())
        {
            root[x] = x;
            rank[x] = 0;
            size[x] = 1;
            return x;
        }
        if (root[x] == x)
            return x;
        root[x] = find_root(root[x]);
        return root[x];
    }

    void unite(int a, int b)
    {
        int ra = find_root(a);
        int rb = find_root(b);
        if (ra == rb)
            return;
        num_combine++;
        if (rank[ra] < rank[rb])
        {
            root[ra] = rb;
            size[rb] += size[ra];
        }
        else if (rank[ra] == rank[rb])
        {
            root[ra] = rb;
            size[rb] += size[ra];
            rank[rb]++;
        }
        else
        {
            root[rb] = ra;
            size[ra] += size[rb];
        }
    }

    int get_num_combine()
    {
        return num_combine;
    }
};

class Kruskal
{
private:
    vector<Edge> e;
    vector<pair<int, int>> mst;

public:
    Kruskal(vector<Edge> &&edges)
    {
        sort(edges.begin(), edges.end(), [](const Edge &e, const Edge &v) {
            return e.weight < v.weight;
        });
        auto uf = UF();
        for (auto const &edge : edges)
        {
            if (uf.find_root(edge.v) != uf.find_root(edge.w))
            {
                uf.unite(edge.v, edge.w);
                mst.emplace_back(edge.v, edge.w);
            }
        }
    }

    vector<pair<int, int>> get_mst()
    {
        return mst;
    }
};

int main()
{
    vector<Edge> edges{{0, 1, 1}, {1, 2, 1}, {2, 0, 1}, {10, 11, 1}, {11, 12, 1}, {12, 10, 1}};
    auto kru = Kruskal(move(edges));
    for (auto const &e : kru.get_mst())
        printf("%d %d\n", e.first, e.second);
    return 0;
}