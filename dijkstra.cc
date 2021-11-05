template <typename TComparer = less<int>> 
class IndexedPQ {
private:
    function<bool(int, int)> comp;
    vector<pair<int, int>> h; // {{key, score}}
    unordered_map<int, int> m; // {{key -> idx}}
    
    void refresh_map(int idx) {
        auto [key, score] = h[idx];
        m[key] = idx;
    }
    
    void swim(int idx) {
        if (idx == 0) {
            return;
        }
        
        while (idx > 0) {
            int parent_idx = (idx - 1) / 2;
            if (this->comp(h[parent_idx].second, h[idx].second)) {
                swap(h[parent_idx], h[idx]);
                refresh_map(parent_idx);
                refresh_map(idx);
            } else {
                break;
            }
            idx = parent_idx;
        }
    }
    
    void sink(int idx) {
        while (true) {
            int left_child_idx = idx * 2 + 1;
            int right_child_idx = idx * 2 + 1;
            if (left_child_idx >= h.size()) {
                break;
            }
            
            int child_idx = right_child_idx >= h.size() || !this->comp(h[left_child_idx].second, h[right_child_idx].second) ? left_child_idx : right_child_idx;
            
            if (this->comp(h[idx].second, h[child_idx].second)) {
                swap(h[idx], h[child_idx]);
                refresh_map(idx);
                refresh_map(child_idx);
            } else {
                break;
            }
            idx = child_idx;
        }
    }
    
public:
    IndexedPQ() : comp(TComparer()) {}
    
    int get_score(int key) {
        if (!m.count(key)) {
            throw exception();
        }
        
        return h[m.at(key)].second;
    }
    
    void upsert(int key, int score) {
        if (m.count(key)) {
            int idx = m.at(key);
            h[idx].second = score;
            swim(idx);
            sink(idx);
        } else {
            h.emplace_back(key, score);
            int idx = h.size() - 1;
            m[key] = idx;
            swim(idx);
        }
    }
    
    pair<int, int> top() {
        if (h.empty()) {
            throw exception();
        }
        
        return h[0];
    }
    
    pair<int, int> pop() {
        if (h.empty()) {
            throw exception();
        }
        
        return del(h[0].first);
    }
    
    pair<int, int> del(int key) {
        if (!m.count(key)) {
            throw exception();
        }
        
        int idx = m.at(key);
        pair<int, int> result = h[idx];
        if (h.size() == 1) {
            h.pop_back();
            m.clear();
        } else {
            m.erase(h[idx].first);
            h[idx] = h.back();
            refresh_map(idx);
            h.pop_back();
            swim(idx);
            sink(idx);
        }
        
        return result;
    }
    
    int size() {
        return h.size();
    }
    
    void print_all() {
        for (auto const& [key, score] : h) {
            printf("%d %d | ", key, score);
        }
        cout << endl;
        print_map();
    }
    
    void print_map() {
        for (auto const& [key, idx] : m) {
            printf("%d->%d |", key, idx);
        }
        cout << endl;
    }
};


class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> adj(n);
        
        for (auto const& time : times) {
            adj[time[0] - 1].emplace_back(time[1] - 1, time[2]);
        }
        
        k--;
        
        IndexedPQ<greater<int>> pq;
        vector<int> d(n, 1e9 + 7);
        d[k] = 0;
        pq.upsert(k, 0);
        while (pq.size()) {
            auto [node, distance] = pq.pop();
            for (auto const& [nxt, weight] : adj[node]) {
                if (distance + weight < d[nxt]) {
                    d[nxt] = distance + weight;
                    pq.upsert(nxt, d[nxt]);
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
