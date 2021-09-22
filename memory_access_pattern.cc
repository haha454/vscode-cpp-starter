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

int main()
{
    const int N = 1e4;
    vector<vector<int>> a(N, vector<int>(N));

    const clock_t t0 = clock();
    // keyword: locality of reference, spatial locality
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = a[i][j];

    const clock_t t1 = clock();
    printf("spent %f seconds on accessing matrix from dimension i to dimension j\n", float(t1 - t0) / CLOCKS_PER_SEC);

    const clock_t t2 = clock();
    for (int j = 0; j < N; j++)
        for (int i = 0; i < N; i++)
            a[i][j] = a[i][j];

    const clock_t t3 = clock();
    printf("spent %f seconds on accessing matrix from dimension j to dimension i\n", float(t3 - t2) / CLOCKS_PER_SEC);
    return 0;
}