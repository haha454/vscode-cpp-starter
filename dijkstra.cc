template<
    class TComparer = std::less<int>
>
class IndexedPQ {
private:
    vector<pair<int, int>> h;
    unordered_map<int, int> key_idx_map;
    function<bool (int, int)> comp;
    
    void refresh_map(int idx) {
        if (idx >= h.size()) {
            return;
        }
        key_idx_map[h[idx].first] = idx;    
    }
    
    void sink(int idx) {
        int n = h.size();
        while (true) {
            int left_idx = 2 * idx + 1, right_idx = 2 * idx + 2;
            if (left_idx >= n) {
                break;
            }
            
            int child_idx = left_idx;
            if (right_idx < n && this->comp(h[child_idx].second, h[right_idx].second)) {
                child_idx = right_idx;
            }
            
            if (!this->comp(h[idx].second, h[child_idx].second)) {
                break;
            }
                
            swap(h[idx], h[child_idx]);
            refresh_map(idx);
            refresh_map(child_idx);
            idx = child_idx;
        }
    }
    
    void swim(int idx) {
        if (idx >= h.size()) {
            return;
        }
        
        while (idx > 0) {
            int parent_idx = (idx - 1) / 2;
            
            if (!this->comp(h[parent_idx].second, h[idx].second)) {
                break;
            }
                
            swap(h[parent_idx], h[idx]);
            refresh_map(parent_idx);
            refresh_map(idx);
            idx = parent_idx;
        }
    }
    
public:
    IndexedPQ() : comp(TComparer()) {}
    
    void insert(int key, int score) {
        if (!key_idx_map.count(key)) {
            h.emplace_back(key, score);
            refresh_map(h.size() - 1);
            swim(h.size() - 1);
        } else {
            int idx = key_idx_map.at(key);
            h[idx].second = score;
            swim(idx);
            sink(idx);
        }
    }
    
    pair<int, int> top() {
        if (h.empty()) {
            throw exception();
        }
        
        return h[0];
    }
    
    void pop() {
        if (h.empty()) {
            throw exception();
        }
        
        swap(h[0], h.back());
        key_idx_map.erase(h.back().first);
        h.pop_back();
        refresh_map(0);
        sink(0);
    }
    
    void del(int key) {
        if (!key_idx_map.count(key)) {
            return;
        }
        
        int idx = key_idx_map.at(key);
        // printf("map: %d->%d\n", key, idx);
        swap(h[idx], h.back());
        key_idx_map.erase(h.back().first);
        h.pop_back();
        refresh_map(idx);
        swim(idx);
        sink(idx);
    }
    
    int size() {
        return h.size();
    }
    
    void print_map() {
        for (auto const& [key, idx] : key_idx_map) {
            printf("%d->%d |", key, idx);
        }
        cout << endl;
    }
    
    void print_all() {
        for (auto const& [key, score] : h) {
            printf("k: %d s:%d |", key, score);
        }
        cout << endl;
    }
};

class Solution {
public:
    // find shortest path from s to e, assume that there is no edges with negative weights
    // https://leetcode.com/problems/network-delay-time
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> adj(n);
        
        for (auto const& time : times) {
            adj[time[0] - 1].emplace_back(time[1] - 1, time[2]);
        }
        
        k--;
        
        IndexedPQ<greater<int>> pq;
        vector<int> d(n, 1e9 + 7);
        d[k] = 0;
        pq.insert(k, 0);
        while (pq.size()) {
            auto [node, distance] = pq.top();
            pq.pop();
            for (auto const& [nxt, weight] : adj[node]) {
                if (distance + weight < d[nxt]) {
                    d[nxt] = distance + weight;
                    pq.insert(nxt, d[nxt]);
                }
            }
        }
        
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, d[i]);
        }
        
        return ans > 1e9 ? -1 : ans;
    }
};
