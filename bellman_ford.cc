#include "trace.hh"
#include <bits/stdc++.h>

const double PI = 4 * atan(1);
const int INF = 1e9 + 7;
using namespace std;

// assume there is no negative cycle; otherwise the constructor will result in infinite loop.
class BellmanFord
{
private:
    vector<int> d;

public:
    BellmanFord(vector<vector<pair<int, int>>> &&graph, int s)
    {
        d.assign(graph.size(), INF);
        unordered_set<int> inq;
        queue<int> q;
        d[s] = 0;
        q.push(s);
        inq.insert(s);
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            inq.erase(v);
            for (auto const &p : graph[v])
            {
                int w = p.first;
                int weight = p.second;
                if (d[w] > d[v] + weight)
                {
                    d[w] = d[v] + weight;
                    if (!inq.count(w))
                    {
                        q.push(w);
                        inq.insert(w);
                    }
                }
            }
        }
    }

    int dist(int w)
    {
        return d[w];
    }
};

int main()
{
    int n, a, b, m;
    cin >> n;
    vector<vector<pair<int, int>>> graph(n);
    for (int i = 0; i < n; i++)
    {
        cin >> m;
        while (m--)
        {
            cin >> a >> b;
            graph[i].emplace_back(a, b);
        }
    }
    auto bf = BellmanFord(move(graph), 0);
    for (int i = 0; i < n; i++)
    {
        printf("%d %d\n", i, bf.dist(i));
    }
    return 0;
}