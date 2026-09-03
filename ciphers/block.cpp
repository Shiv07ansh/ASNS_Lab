#include <iostream>
using namespace std;

int F(int right, int key)
{
    return (right ^ key) + 3;
}

int encrypt(int block, int key)
{
    int left = block / 16;
    int right = block % 16;

    for (int i = 0; i < 4; i++)
    {
        int newRight = left ^ (F(right, key) % 16);

        left = right;
        right = newRight;
    }

    return left * 16 + right;
}

int decrypt(int block, int key)
{
    int left = block / 16;
    int right = block % 16;

    for (int i = 0; i < 4; i++)
    {
        int newLeft = right ^ (F(left, key) % 16);

        right = left;
        left = newLeft;
    }

    return left * 16 + right;
}

int main()
{
    int plaintext, key;

    cout << "Enter plaintext (0-255): ";
    cin >> plaintext;

    cout << "Enter key (0-15): ";
    cin >> key;

    int ciphertext = encrypt(plaintext, key);
    int decrypted = decrypt(ciphertext, key);

    cout << "\nPlaintext  : " << plaintext;
    cout << "\nCiphertext : " << ciphertext;
    cout << "\nDecrypted  : " << decrypted;

    return 0;
}