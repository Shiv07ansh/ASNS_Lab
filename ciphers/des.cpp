#include <iostream>
using namespace std;

int IP[8] = {2, 6, 3, 1, 4, 8, 5, 7};
int FP[8] = {4, 1, 3, 5, 7, 2, 8, 6};
int E[8]  = {4, 1, 2, 3, 2, 3, 4, 1};
int P[4]  = {2, 4, 3, 1};

int S[4][4] =
{
    {14, 4, 13, 1},
    {2, 15, 11, 8},
    {3, 10, 6, 5},
    {12, 9, 0, 7}
};

int permute(int value, int table[], int size)
{
    int result = 0;

    for (int i = 0; i < size; i++)
    {
        int bit = (value >> (8 - table[i])) & 1;
        result = (result << 1) | bit;
    }

    return result;
}

int F(int right, int key)
{
    int expanded = permute(right, E, 8);
    int x = expanded ^ key;

    int row = (x >> 2) & 3;
    int column = x & 3;

    int s = S[row][column];

    int result = 0;

    for (int i = 0; i < 4; i++)
    {
        int bit = (s >> (4 - P[i])) & 1;
        result = (result << 1) | bit;
    }

    return result;
}

int encrypt(int plaintext, int key)
{
    int data = permute(plaintext, IP, 8);

    int left = data >> 4;
    int right = data & 15;

    for (int i = 0; i < 4; i++)
    {
        int newRight = left ^ F(right, key);

        left = right;
        right = newRight;
    }

    int combined = (left << 4) | right;

    return permute(combined, FP, 8);
}

int decrypt(int ciphertext, int key)
{
    int data = permute(ciphertext, IP, 8);

    int left = data >> 4;
    int right = data & 15;

    for (int i = 0; i < 4; i++)
    {
        int newLeft = right ^ F(left, key);

        right = left;
        left = newLeft;
    }

    int combined = (left << 4) | right;

    return permute(combined, FP, 8);
}

int main()
{
    int plaintext, key;

    cout << "Enter plaintext (0-255): ";
    cin >> plaintext;

    cout << "Enter key (0-255): ";
    cin >> key;

    int ciphertext = encrypt(plaintext, key);
    int decrypted = decrypt(ciphertext, key);

    cout << "Ciphertext: " << ciphertext << endl;
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}