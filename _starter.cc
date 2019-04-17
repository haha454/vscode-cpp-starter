#include "trace.hh"
#include <bits/stdc++.h>

const double PI = 4 * atan(1);
const int INF = 1e9 + 7;
using namespace std;

int main()
{
    int t;
    std::cin >> t;
    for (int i = 1; i <= t; i++)
    {
        std::cout << "Case #" << i << ": ";
        PRINT(i - 1, i - 1 + i - 1, t - 1);
        TRACE(i, i + i, t);
    }
    return 0;
}