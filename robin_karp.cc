#include <bits/stdc++.h>

using namespace std;

// returns a^x % m
int pow(int a, int x, int m)
{
    if (x == 0)
        return 1;
    int mid = pow(a, x / 2, m);
    if (x % 2 == 0)
        return 1LL * mid * mid % m;
    return 1LL * mid * mid % m * a % m;
}

class RabinKarp
{
private:
    const int MOD = 1e9 + 7;
    const string pat;
    const int R;             // radix
    const long long RM;      // R^(M-1) % MOD
    const long long patHash; // pattern hash value

    long long hash(string &s, int len)
    {
        long long h = 0;
        for (int i = 0; i < len; i++)
            h = (h * R + s[i]) % MOD;
        return h;
    }

    bool check(string &txt, int i)
    {
        for (unsigned int j = 0; j < pat.length(); j++)
            if (pat[j] != txt[i + j])
                return false;
        return true;
    }

public:
    RabinKarp(string &pat) : pat(pat), R(256), RM(pow(R, pat.length() - 1, MOD)), patHash(hash(pat, pat.length()))
    {
    }

    int search(string &txt)
    {
        size_t m = pat.length(), n = txt.length();
        if (n < m)
            return n;

        long long txtHash = hash(txt, m);

        // check for match at offset 0
        if ((patHash == txtHash) && check(txt, 0))
            return 0;

        // check for hash match; if hash match, check for exact match
        for (auto i = m; i < n; i++)
        {
            // Remove leading digit, add trailing digit, check for match.
            txtHash = (txtHash + MOD - RM * txt[i - m] % MOD) % MOD;
            txtHash = (txtHash * R + txt[i]) % MOD;

            // match
            int offset = i - m + 1;
            if ((patHash == txtHash) && check(txt, offset))
                return offset;
        }

        // no match
        return n;
    }
};

int main()
{
    string pat = "abracadabra", txt = "abacadabrabracabracadabrabrabracad";
    auto rk = RabinKarp(pat);
    cout << rk.search(txt);
    return 0;
}