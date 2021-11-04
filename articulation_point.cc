class Solution {
private:
    vector<int> lowLink, seq;
    vector<vector<int>> adj;
    int n, r, c;
    vector<vector<int>> rcm;
    vector<vector<int>> child;
    vector<vector<int>> WALKS = {{0,1},{0,-1},{1,0},{-1,0}};
    int curSeq;
    
    void dfsTree(int cur, int last) {
        curSeq++;
        lowLink[cur] = curSeq;
        seq[cur] = curSeq;
        
        for (auto const& nxt : adj[cur]) {
            if (seq[nxt] == -1) {
                child[cur].push_back(nxt);
                dfsTree(nxt, cur);
                lowLink[cur] = min(lowLink[cur], lowLink[nxt]);
            } else if (nxt != last) {
                lowLink[cur] = min(lowLink[cur], seq[nxt]);
            }
        }
    }
public:
    // https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/submissions/
    int minDays(vector<vector<int>>& a) {
        int r = a.size(); c = a[0].size();
        rcm.assign(r, vector<int>(c, -1));
        this->n = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (a[i][j] == 1) {
                    rcm[i][j] = n++;
                    adj.push_back({});
                }
            }
        }
        
        
        if (n == 1) {
            return 1;
        }
        
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++) {
                if (rcm[i][j] != -1) {
                    int cur = rcm[i][j];
                    for (auto const& walk : WALKS) {
                        int nr = i + walk[0], nc = j + walk[1];
                        if (nr >= 0 && nr < r && nc >= 0 && nc < c && rcm[nr][nc] != -1) {
                            adj[cur].push_back(rcm[nr][nc]);
                        }
                    }
                }
            }
        lowLink.assign(n, -1);
        seq.assign(n, -1);
        child.resize(n);
        curSeq = 0;
        dfsTree(0, -1);
        
        for (int i = 1; i < n; i++) {
            if (seq[i] == -1) {
                return 0;
            }
        }
        
        if (child[0].size() > 1) {
            return 1;
        }
        
        for (int i = 1; i < n; i++) {
            for (auto const& nxt : child[i]) {
                if (seq[i] <= lowLink[nxt]) {
                    return 1;
                }
            }
        }
        
        return 2;
    }
};
