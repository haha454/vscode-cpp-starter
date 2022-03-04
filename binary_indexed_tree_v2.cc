class BIT {
public:
    vector<int> sum;
    int n;
    
    BIT(int n) : n(n), sum(n + 1, 0) {}
    
    void update(int idx, int delta) {
        idx++;
        while (idx <= n) {
            sum[idx] += delta;
            idx += idx & (-idx);
        }
    }
    
    // exclusive
    int getSum(int i) {
        int result = 0;
        while (i) {
            result += sum[i];
            i &= i - 1;
        }
        
        return result;
    }
};

// https://leetcode.com/problems/count-good-triplets-in-an-array/
class Solution {
public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> indices(n);
        for (int i = 0; i < n; i++) {
            indices[nums1[i]] = i;
        }
        
        long long ans = 0;
        BIT bit = BIT(n);
        for (int i = 0; i < n; i++) {
            auto num = nums2[i];
            
            int idx = indices[num];
            int left_num = bit.getSum(idx);
            int right_num = n - (idx + 1) - (bit.getSum(n) - bit.getSum(idx + 1));
            ans += 1LL * left_num * right_num;
            
            bit.update(idx, 1);
        }
        
        return ans;
    }
};
