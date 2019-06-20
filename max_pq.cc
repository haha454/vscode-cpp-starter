#include "trace.hh"
#include <bits/stdc++.h>

using namespace std;

class MaxPQ
{
private:
    vector<int> pq;

    inline int parent(int x)
    {
        return (x - 1) >> 1;
    }

    inline int left(int x)
    {
        return 2 * x + 1;
    }

    inline int right(int x)
    {
        return 2 * x + 2;
    }

public:
    MaxPQ()
    {
    }

    bool empty()
    {
        return pq.empty();
    }

    int size()
    {
        return pq.size();
    }

    int top()
    {
        if (empty())
            throw exception();
        return pq.front();
    }

    void insert(int x)
    {
        pq.push_back(x);
        swim(pq.size() - 1);
    }

    void swim(int k)
    {
        while (k > 0 && less(parent(k), k))
        {
            exch(k, parent(k));
            k = parent(k);
        }
    }

    void sink(int k)
    {
        while (left(k) < size())
        {
            int j = left(k);
            if (j < size() - 1 && less(j, j + 1))
                j++;
            if (!less(k, j))
                break;
            exch(k, j);
            k = j;
        }
    }

    bool less(int i, int j)
    {
        return pq[i] < pq[j];
    }

    void exch(int i, int j)
    {
        swap(pq[i], pq[j]);
    }

    int del_top()
    {
        if (empty())
            throw exception();
        int result = pq.front();
        swap(pq.front(), pq.back());
        pq.pop_back();
        sink(0);
        return result;
    }
};

int main()
{
    MaxPQ maxpq;
    int a;
    while (scanf("%d", &a) != EOF)
    {
        maxpq.insert(a);
        cout << maxpq.top() << endl;
    }

    while (!maxpq.empty())
    {
        cout << maxpq.del_top() << endl;
    }
    return 0;
}