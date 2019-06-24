#include <iostream>

using namespace std;

int main()
{
    unsigned char ch;
    while (scanf("%c", &ch) != EOF)
    {
        cout << hex << 0 + ch;
        cout << ' ';
    }
    return 0;
}