#include <vector>
#include <unordered_set>
#include <queue>
#include <iostream>
#include <algorithm>

// Unlike dijkstra, bellman ford works for shortest distance problem with negative distance edges.
// Caveat: assume there is no negative cycle; otherwise bellman ford algorithm will never complete.
class BellmanFord
{
private:
    std::vector<int> dist_;

public:
    BellmanFord(const std::vector<std::vector<std::pair<int, int>>>& adj, int s)
    {
        dist_.assign(adj.size(), -1);
        std::queue<int> q;
        std::unordered_set<int> q_set;
        dist_[s] = 0;
        q.push(s);
        q_set.insert(s);
        while (!q.empty())
        {
            auto cur{q.front()};
            q.pop();
            q_set.erase(cur);
            for (auto const &[nxt, nxt_dist] : adj[cur])
            {
                if (dist_[nxt] == -1 || dist_[cur] + nxt_dist < dist_[nxt])
                {
                    dist_[nxt] = dist_[cur] + nxt_dist;
                    if (!q_set.count(nxt))
                    {
                        q.push(nxt);
                        q_set.insert(nxt);
                    }
                }
            }
        }
    }

    int GetShortestDistance(int w) const
    {
        return dist_[w];
    }

    int GetMaxShortestDistance() const {
        return *std::max_element(dist_.cbegin(), dist_.cend());
    }

    bool AllReachable() const {
        return std::all_of(dist_.cbegin(), dist_.cend(), [](int dist)
                           { return dist >= 0; });
    }
};

class Solution {
public:
    // https://leetcode.com/problems/network-delay-time/description/
    int networkDelayTime(const std::vector<std::vector<int>>& times, int n, int k) {
        std::vector<std::vector<std::pair<int, int>>> adj(n);
        for (auto const &time : times)
        {
            adj[time[0] - 1].emplace_back(time[1] - 1, time[2]);
        }

        BellmanFord bf{adj, k - 1};
        if (!bf.AllReachable()) {
            return -1;
        }

        return bf.GetMaxShortestDistance();
    }
};

int main()
{
    int n, a, b, m;
    std::cin >> n;
    std::vector<std::vector<std::pair<int, int>>> adj(n);
    for (auto i{0}; i < n; i++)
    {
        std::cin >> m;
        while (m--)
        {
            std::cin >> a >> b;
            adj[i].emplace_back(a, b);
        }
    }
    auto bf{BellmanFord(adj, 0)};
    for (auto i{1}; i < n; i++)
    {
        std::cout << "Distance from 0 to " << i << ": " << bf.GetShortestDistance(i) << std::endl;
    }
    return 0;
}