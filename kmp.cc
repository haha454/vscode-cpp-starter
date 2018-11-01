#include <bits/stdc++.h>

using namespace std;

void construct_lps(string &p, vector<int> &lps)
{
    int n = p.length();
    lps.resize(n);
    lps[0] = 0;
    for (int i = 1; i < n; i++)
    {
        int prev_len = lps[i - 1];
        while (prev_len != 0 && p[i] != p[prev_len])
            prev_len = lps[prev_len - 1];
        lps[i] = prev_len + (p[i] == p[prev_len]);
    }
}

void kmp(string &s, string &p)
{
    vector<int> lps;
    construct_lps(p, lps);
    int n = s.length();
    int m = p.length();
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == p[j])
        {
            j++;
            if (j == m)
            {
                printf("%d\n", i);
                j = lps[j - 1];
            }
        }
        else
        {
            while (j != 0 && s[i] != p[j])
            {
                j = lps[j - 1];
            }
            j += (s[i] == p[j]);
        }
    }
}

int main()
{
    string s;
    string p;
    getline(cin, s);
    getline(cin, p);
    kmp(s, p);
    return 0;
}