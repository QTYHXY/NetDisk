#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char const *argv[])
{
    string s;
    cin >> s;

    int step = 'a' - 'A';

    // 1，C语言风格遍历与替换
    string s1 = s;
    for (int i = 0; i < strlen(s1.data()); i++)
    {
        if ('A' <= s1[i] && s1[i] <= 'Z')
            s1[i] += step;
        else if ('a' <= s1[i] && s1[i] <= 'z')
            s1[i] -= step;
    }
    cout << s1 << endl;

    // 2，C++新式遍历
    string s2 = s;
    for (char x : s2)
    {
        if (isupper(x))
            cout << char(x + step);
        else if (islower(x))
            cout << char(x - step);
        else
            cout << x;
    }
    cout << endl;

    return 0;
}