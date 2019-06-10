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

// https://en.wikipedia.org/wiki/Modular_multiplicative_inverse Using Euler's theorem

// input: integer a, prime number m
// output: x such that ax % m == 1
// principle: a^(-1) % m == a^(m - 2) % m
int euler(int a, int m)
{
    return pow(a, m - 2, m);
}

int main()
{
    printf("%d\n", euler(99, 1e9 + 7));
    return 0;
}