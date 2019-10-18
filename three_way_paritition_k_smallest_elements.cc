#include<bits/stdc++.h>

using namespace std;

void partition(vector<int>& a, int l, int r, int& p1, int& p2){
    if (l == r)
    {
        p1 = p2 = l;
        return;
    }
    int i = l + 1;
    while (i <= r){
        if (a[i] > a[l])
        {
            swap(a[i], a[r]);
            r--;
        }
        else if (a[i] < a[l])
        {
            swap(a[i], a[l]);
            i++;
            l++;
        }
        else
            i++;
    }
    p1 = l;
    p2 = r;
}

int main()
{
    string line;
    getline(cin, line);
    istringstream iss(line);
    vector<int> a = vector<int>(istream_iterator<int>(iss), istream_iterator<int>());
    int k;
    cin >> k;
    int p1 = 0, p2 = -1, l = 0, r = a.size() - 1;
    while (k < p1 || k > p2) {
        partition(a, l, r, p1, p2);
        if (k < p1)
            r = p1 - 1;
        if (k > p2)
            l = p2 + 1;
    }

    for (auto & v : a)
        printf("%d ", v);
    printf("\n%d %d\n", p1, p2);
    
    return 0;
}