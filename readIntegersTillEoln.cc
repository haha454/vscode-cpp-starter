#include <bits/stdc++.h>

using namespace std;

int main()
{
    string line;
    while (getline(cin, line))
    {
        istringstream iss(line);
        vector<int> v = vector<int>(istream_iterator<int>(iss), istream_iterator<int>());
        for (auto const &a : v)
            printf("%d ", a);
        printf("\n");
    }
}