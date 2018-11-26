#include <bits/stdc++.h>

using namespace std;

class UF
{
  private:
    unordered_map<int, int> root;
    unordered_map<int, int> rank;
    int num_combine;

  public:
    UF() : num_combine(0)
    {
    }

    int find_root(int x)
    {
        if (root.find(x) == root.end())
        {
            root[x] = x;
            rank[x] = 1;
            return x;
        }
        if (root[x] == x)
            return x;
        root[x] = find_root(root[x]);
        return root[x];
    }

    void combine(int a, int b)
    {
        int ra = find_root(a);
        int rb = find_root(b);
        if (ra == rb)
            return;
        num_combine++;
        if (rank[ra] > rank[rb])
        {
            root[rb] = ra;
        }
        else
            root[ra] = rb;
    }

    int get_num_combine()
    {
        return num_combine;
    }
};

int main()
{
    int a, b;
    auto uf = new UF();
    while (!cin.eof())
    {
        scanf("%d%d", &a, &b);
        uf->combine(a, b);
        printf("Combined %d times.\n", uf->get_num_combine());
    }
    delete uf;
    return 0;
}