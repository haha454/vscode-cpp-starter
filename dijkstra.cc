int dijkstra(vector<vector<int>> a, int s, int e)
{
    int n = a.size();
    vi d = vi(n, INT_MAX);
    d[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({d[s], s});
    while (!pq.empty())
    {
        int node = pq.top().second;
        pq.pop();
        if (node == e)
            return d[node];
        F0R(i, n - 1)
        {
            if (a[node][i] != -1)
                if (d[node] + a[node][i] < d[i])
                {
                    d[i] = d[node] + a[node][i];
                    pq.push({d[i], i});
                }
        }
    }
    return -1;
}