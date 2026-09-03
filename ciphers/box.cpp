#include <iostream>
using namespace std;

// P-Box
int P[4] = {2, 4, 3, 1};

// S-Box
int S[4][4] =
{
    {14, 4, 13, 1},
    {2, 15, 11, 8},
    {3, 10, 6, 5},
    {12, 9, 0, 7}
};

int SBox(int x)
{
    int row = (x >> 2) & 3;
    int column = x & 3;

    return S[row][column];
}

int PBox(int x)
{
    int result = 0;

    for (int i = 0; i < 4; i++)
    {
        int bit = (x >> (4 - P[i])) & 1;
        result = (result << 1) | bit;
    }

    return result;
}

int main()
{
    int input;

    cout << "Enter 4-bit input (0-15): ";
    cin >> input;

    int s = SBox(input);
    int p = PBox(s);

    cout << "After S-Box: " << s << endl;
    cout << "After P-Box: " << p << endl;

    return 0;
}