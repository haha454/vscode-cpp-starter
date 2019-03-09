#include <bits\stdc++.h>

using namespace std;

class Fraction
{
  public:
    long long num, den;

    Fraction(long long num, long long den) : num(num), den(den) { reduce(); }
    void reduce()
    {
        long long gcd = __gcd(num, den);
        num /= gcd;
        den /= gcd;
    }
    Fraction operator+(const Fraction &other)
    {
        Fraction x = Fraction(num * other.den + other.num * den, den * other.den);
        return x;
    }

    bool operator==(const Fraction &other) const
    {
        return num == other.num && den == other.den;
    }
};

namespace std
{

template <>
struct hash<Fraction>
{
    std::size_t operator()(const Fraction &k) const
    {
        using std::hash;
        using std::size_t;

        // Compute individual hash values for first,
        // second and third and combine them using XOR
        // and bit shifting:

        return (hash<long long>()(k.num) ^ (hash<long long>()(k.den) << 1)) >> 1;
    }
};

} // namespace std

int main()
{
    Fraction f1 = Fraction(2, 6);
    Fraction f2 = Fraction(1, 3);
    printf("%d %d\n", hash<Fraction>{}(f1), hash<Fraction>{}(f2));
    unordered_set<Fraction> s;
    s.insert(f1);
    s.insert(f2);
    printf("%d", s.size());
    return 0;
}