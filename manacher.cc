#include <bits/stdc++.h>
using namespace std;

vector<int> find_palindrome(const string &s)
{
    string ss = "$";
    for (auto const &c : s)
    {
        ss += c;
        ss += '#';
    }
    ss.pop_back();
    ss += '@';
    cout << ss << endl;
    int n = ss.length();
    vector<int> p(n, 0);

    int centre = 0, right = 0;

    for (int i = 1; i < n; i++){
        if (i <= right) {
            int mirror = 2 * centre - i;
            assert(mirror >= 0);
            p[i] = min(right - i, p[mirror]);
        }

        while (ss[i + p[i] + 1] == ss[i - (p[i] + 1)])
            p[i]++;

        if (i + p[i] > right) {
            centre = i;
            right = i + p[i];
        }
    }

    return p;
}

int main()
{
    string s;
    getline(cin, s);
    auto ans = find_palindrome(s);
    for (size_t i = 0; i < ans.size(); i++)
        printf("%d %d\n", i, ans[i]);
}