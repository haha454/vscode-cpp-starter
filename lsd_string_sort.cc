#include "trace.hh"
#include <bits/stdc++.h>

const double PI = 4 * atan(1);
const int INF = 1e9 + 7;
using namespace std;

inline char char_at(string &a, int pos)
{
    if (pos >= a.length())
        return 0;
    return a.at(pos);
}
void sort(vector<string> &a, int W)
{
    int R = 256;
    int N = a.size();
    string aux[N];
    for (int d = W - 1; d >= 0; d--)
    {
        vector<int> count(R + 1, 0);
        for (int i = 0; i < N; i++)
            count[char_at(a[i], d) + 1]++;
        for (int r = 0; r < R; r++)
            count[r + 1] += count[r];
        for (int i = 0; i < N; i++)
            aux[count[char_at(a[i], d)]++] = a[i];
        for (int i = 0; i < N; i++)
            a[i] = aux[i];
    }
}

int main()
{
    vector<string> a{"haha", "ahha", "hah", "ahh"};
    sort(a, 100);
    for (auto const &s : a)
        cout << s << endl;
    return 0;
}