#include <bits/stdc++.h>

using namespace std;

// https://en.wikipedia.org/wiki/Modular_multiplicative_inverse section Extended Euclidean algorithm
// input: int a, int b
// output: int x, int y so that ax + by == gcd(a, b)
// return gcd(a,b)

// if b is prime, say 1e9+7, then we can get ax % b = 1
// we can get other x values by rewrite the above equation as a(x + b) + b(y -  a) == gcd(a, b)
int extended_gcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    int next_x, next_y;
    int gcd = extended_gcd(b, a % b, next_x, next_y);
    x = next_y;
    y = next_x - a / b * next_y;
    return gcd;
}

// problem: given arrays num[0..n-1] and rem[0..n-1]. In num[0..n-1], every pair is coprime. Find out minimum positive number x such that
// x % num[i] == rem[i] for 0 <= i < n
// returns: x
// principle: for each pair of num[i] and rem[i] find xi such that num[0] * num[1] * ... * num[i - 1] * num[i + 1] * ... num[n - 1] * xi % num[i] == rem[i]
// as num[0] * num[1] * ... * num[i - 1] * num[i + 1] * ... num[n - 1] * xi % <anyother num[k]> == 0 but % num[i] == rem[i]
// such num[0] * num[1] * ... * num[i - 1] * num[i + 1] * ... num[n - 1] * xi contributes to final x
int chinese_remainder(vector<int> &num, vector<int> &rem)
{
    assert(num.size() == rem.size());
    int n = num.size();

    int ans = 0, product = 1;
    for (int i = 0; i < n; i++)
    {
        product *= num[i];
    }
    for (int i = 0; i < n; i++)
    {
        int other_product = product / num[i];
        int x, y;
        int gcd = extended_gcd(other_product, num[i], x, y);
        assert(gcd == 1);
        ans = (ans + other_product * x * rem[i]) % product;
    }
    return ans < 0 ? ans + product : ans;
}

int main()
{
    vector<int> num{3, 4, 5}, rem{2, 3, 1};
    printf("%d\n", chinese_remainder(num, rem));
    return 0;
}