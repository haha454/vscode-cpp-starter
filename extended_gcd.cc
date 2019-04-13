#include <bits/stdc++.h>

using namespace std;

// input: int a, int b
// output: int x, int y so that ax + by == gcd(a, b)
// return gcd(a,b)
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
int main()
{
    int x, y;
    printf("%d\n", extended_gcd(99, 78, x, y));
    printf("%d %d", x, y);
    return 0;
}