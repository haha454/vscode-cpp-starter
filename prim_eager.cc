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
            int right_child_idx = idx * 2 + 2;
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
        // print_map();
    }
    
    void print_map() {
        for (auto const& [key, idx] : m) {
            printf("%d->%d |", key, idx);
        }
        cout << endl;
    }
};

// https://leetcode.com/problems/min-cost-to-connect-all-points/submissions/
class Solution {
private:
    int abs(int a) {
        return a < 0 ? -a : a;
    }
    
    int get_dis(vector<int>& a, vector<int>&b ) {
        return abs(a[0] - b[0]) + abs(a[1] - b[1]);    
    }
public:
    // lazy update weight version
//     int minCostConnectPoints(vector<vector<int>>& a) {
//         int n = a.size();
//         vector<bool> visited(n, false);
//         visited[0] = true;
//         priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
//         for (int i = 1; i < n; i++) {
//             pq.emplace(get_dis(a[i], a[0]), i);
//         }
        
//         int ans = 0;
//         while (pq.size()) {
//             // pq.print_all();
//             auto [distance, node] = pq.top();
//             pq.pop();
//             if (visited[node]) {
//                 continue;
//             }
//             visited[node] = true;
//             ans += distance;
//             for (int i = 0; i < n; i++) {
//                 if (visited[i]) {
//                     continue;
//                 }
//                 int cur_dis = get_dis(a[i], a[node]);
//                 pq.emplace(cur_dis, i);
//             }
//         }
        
//         return ans;
//     }
    
    // eager update weight version
  
    int minCostConnectPoints(vector<vector<int>>& a) {
        int n = a.size();
        vector<bool> visited(n, false);
        visited[0] = true;
        IndexedPQ<greater<int>> pq = IndexedPQ<greater<int>>();
        for (int i = 1; i < n; i++) {
            pq.upsert(i, get_dis(a[i], a[0]));
        }
        
        int ans = 0;
        while (pq.size()) {
            // pq.print_all();
            auto [node, distance] = pq.pop();
            // pq.print_all();
            if (visited[node]) {
                continue;
            }
            visited[node] = true;
            ans += distance;
            for (int i = 0; i < n; i++) {
                if (visited[i]) {
                    continue;
                }
                int cur_dis = get_dis(a[i], a[node]);
                if (cur_dis < pq.get_score(i)) {
                    pq.upsert(i, cur_dis);
                }
            }
            
            // printf("ans=%d\n", ans);
        }
        
        return ans;
    }
};
