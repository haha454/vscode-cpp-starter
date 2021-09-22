#include <algorithm>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include <iostream>
#include <string>
#include <random>

using namespace std;

int find_smaller_numbers(const vector<int>& a, const int& threshold) {
    int result = 0;
    for (auto const &aa : a)
    {
        if (aa < threshold) {
            result++;
        }
    }

    return result;
}

int main()
{
    const int N = 1e7;
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        a.push_back(i);
    }

    const clock_t t0 = clock();
    int num_smaller_unsorted = find_smaller_numbers(a, 5);
    const clock_t t1 = clock();
    printf("spent %f seconds on finding smaller numbers in the sorted array; result=%d\n", float(t1 - t0) / CLOCKS_PER_SEC, num_smaller_unsorted);

    shuffle(a.begin(), a.end(), default_random_engine{});
    const clock_t t2 = clock();
    int num_smaller_sorted = find_smaller_numbers(a, 5);
    const clock_t t3 = clock();
    printf("spent %f seconds on finding smaller numbers in the shuffled array; result=%d\n", float(t3 - t2) / CLOCKS_PER_SEC, num_smaller_sorted);
    return 0;
}