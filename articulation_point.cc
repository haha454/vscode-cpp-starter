#include <iostream>
#include <vector>

class Solution {
private:
  std::vector<int> low_link_, seq_;
  std::vector<std::vector<int>> adj_;
  std::vector<std::vector<int>> child_;
  const std::vector<std::vector<int>> kWalks{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  int cur_seq_;

  void DfsTree(int cur, int last) {
    cur_seq_++;
    low_link_[cur] = cur_seq_;
    seq_[cur] = cur_seq_;

    for (auto const &nxt : adj_[cur]) {
      if (seq_[nxt] == -1) {
        child_[cur].push_back(nxt);
        DfsTree(nxt, cur);
        low_link_[cur] = std::min(low_link_[cur], low_link_[nxt]);
      } else if (nxt != last) {
        low_link_[cur] = std::min(low_link_[cur], seq_[nxt]);
      }
    }
  }

public:
  // https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/submissions/
  int minDays(std::vector<std::vector<int>> a) {
    int r{static_cast<int>(a.size())}, c{static_cast<int>(a[0].size())};
    auto rcm = std::vector<std::vector<int>>(r, std::vector<int>(c, -1));
    auto n{0};
    for (auto i{0}; i < r; i++)
      for (auto j{0}; j < c; j++) {
        if (a[i][j] == 1) {
          rcm[i][j] = n++;
          adj_.push_back({});
        }
      }

    if (n == 0) {
      return 0;
    }
    
    if (n == 1) {
      return 1;
    }

    for (auto i{0}; i < r; i++)
      for (auto j{0}; j < c; j++) {
        if (rcm[i][j] != -1) {
          for (auto const &walk : kWalks) {
            auto nr{i + walk[0]}, nc{j + walk[1]};
            if (nr >= 0 && nr < r && nc >= 0 && nc < c && rcm[nr][nc] != -1) {
              adj_[rcm[i][j]].push_back(rcm[nr][nc]);
            }
          }
        }
      }

    low_link_.assign(n, -1);
    seq_.assign(n, -1);
    child_.resize(n);
    cur_seq_ = 0;
    DfsTree(0, -1);

    // already disconnected
    for (auto i{1}; i < n; i++) {
      if (seq_[i] == -1) {
        return 0;
      }
    }

    if (child_[0].size() > 1) {
      return 1;
    }

    for (auto i{1}; i < n; i++) {
      for (auto const &nxt : child_[i]) {
        if (seq_[i] <= low_link_[nxt]) {
          return 1;
        }
      }
    }

    return 2;
  }
};

int main() {
  std::cout << Solution().minDays({{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}})
            << std::endl;
  std::cout << Solution().minDays({{0, 0}}) << std::endl;
  std::cout << Solution().minDays({{1, 0}}) << std::endl;
}