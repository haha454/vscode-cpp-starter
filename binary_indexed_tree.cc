#include "trace.hh"
#include <bits/stdc++.h>

using namespace std;

class BinaryIndexedTree
{
private:
    vector<int> a;
    int query_sum(int r)
    {
        int result = 0;
        r++;
        while (r > 0)
        {
            result += a[r];
            r -= r & (-r);
        }
        return result;
    }

public:
    BinaryIndexedTree(vector<int> &x)
    {
        a.assign(x.size() + 1, 0);
        for (unsigned int i = 0; i < x.size(); i++)
            update(i, x[i]);
    }

    void update(unsigned int pos, int delta)
    {
        pos++;

        while (pos < a.size())
        {
            a[pos] += delta;
            pos += pos & (-pos);
        }
    }

    int query_sum(int l, int r)
    {
        return query_sum(r) - query_sum(l - 1);
    }
};

int main()
{
    string s;
    getline(cin, s);
    istringstream iss(s);
    vector<int> v = vector<int>(istream_iterator<int>(iss), istream_iterator<int>());
    auto bit = BinaryIndexedTree(v);
    while (getline(cin, s))
    {
        istringstream iss(s);
        char operation;
        int a, b;
        iss >> operation;
        iss >> a >> b;
        if (operation == 'q')
        {
            int result = bit.query_sum(a, b);
            printf("query [%d,%d] == %d\n", a, b, result);
        }
        else
        {
            bit.update(a, b);
            printf("updated pos %d by %d\n", a, b);
        }
    }
    return 0;
}