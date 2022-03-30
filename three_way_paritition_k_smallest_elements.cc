#include <bits/stdc++.h>

using namespace std;

/*
Use a[l] as the pivot and partition the array [l, r) into three parts; returns pair: <el, er>
where [l, el) is the smaller part
[el, er) is the equal part
[er, r) is the greater part
*/
pair<int, int> partition(vector<int> &a, int l, int r)
{
    assert(l <= r);
    int pivot = a[l];
    int i = l;
    while (i < r)
    {
        if (a[i] > pivot)
        {
            r--;
            swap(a[i], a[r]);
        }
        else if (a[i] < pivot)
        {
            swap(a[i], a[l]);
            i++;
            l++;
        }
        else
        {
            i++;
        }
    }
    return make_pair(l, r);
}

int main()
{
    string line;
    getline(cin, line);
    istringstream iss(line);
    vector<int> a = vector<int>(istream_iterator<int>(iss), istream_iterator<int>());
    int k;
    cin >> k;

    int l = 0, r = a.size();
    while (true)
    {
        auto [el, er] = partition(a, l, r);
        if (k < el)
            r = el;
        else if (k > er)
            l = er + 1;
        else
        {
            break;
        }
    }

    for (auto const &v : a)
        printf("%d ", v);

    return 0;
}