#include <bits/stdc++.h>

using namespace std;

class Sieve
{
  private:
    vector<bool> is_prime;
    vector<int> primes;

  public:
    Sieve(int maximum)
    {
        assert(maximum > 0);
        is_prime.assign(maximum + 1, true);
        is_prime[0] = is_prime[1] = false;
        primes = {2};
        for (int p = 2; p <= maximum; p += 2)
        {
            is_prime[p] = p == 2;
        }

        for (int p = 3; p * p <= maximum; p += 2)
            if (is_prime[p])
                for (int i = p * p; i <= maximum; i += 2 * p)
                    is_prime[i] = false;

        for (int p = 3; p <= maximum; p += 2)
            if (is_prime[p])
                primes.push_back(p);
    }

    bool is_x_prime(int x)
    {
        return is_prime[x];
    }

    vector<int> get_primes()
    {
        return primes;
    }
};

int main()
{
    int n;
    scanf("%d", &n);
    for (auto const &a : Sieve(n).get_primes())
        printf("%d ", a);
    return 0;
}