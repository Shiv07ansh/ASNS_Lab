// ##RSA ALGORITHM IMPLEMENTATION IN C++##

//RSA is an asymmetric encryption algorithm that uses a public key for encryption and a private key for decryption. 
//It generates keys from two large prime numbers, relying on the difficulty of factoring their product. 
//It can also be used for digital signatures, where the private key signs and the public key verifies.

//RSA relies on prime numbers, modular arithmetic, Euler’s totient function, greatest common divisors, and modular inverses.
//Two prime numbers are multiplied to create a public modulus;
//Euler’s totient determines the number of values relatively prime to that modulus;
//a public exponent is chosen that is coprime with the totient;
//and the private exponent is calculated as its modular inverse.
//Encryption and decryption then use modular exponentiation with the public and private exponents respectively.



#include <iostream>
#include <numeric>
using namespace std;

// --------------------------------------------------
// 1. Greatest Common Divisor
// --------------------------------------------------
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// --------------------------------------------------
// 2. Fast Modular Exponentiation
// Computes: (base^exp) % mod
// --------------------------------------------------
long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp /= 2;
    }

    return result;
}

// --------------------------------------------------
// 3. Extended Euclidean Algorithm
// Finds x and y such that:
//
//      ax + by = gcd(a,b)
// --------------------------------------------------
long long extendedGCD(long long a, long long b,
                       long long &x, long long &y) {

    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    long long x1, y1;

    long long g = extendedGCD(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return g;
}

// --------------------------------------------------
// 4. Modular Inverse
//
// Finds d such that:
//
//      (e * d) % phi = 1
// --------------------------------------------------
long long modInverse(long long e, long long phi) {

    long long x, y;

    long long g = extendedGCD(e, phi, x, y);

    if (g != 1) {
        return -1;  // inverse doesn't exist
    }

    x %= phi;

    if (x < 0)
        x += phi;

    return x;
}

// --------------------------------------------------
// 5. RSA
// --------------------------------------------------
int main() {

    // Choose two prime numbers
    long long p = 61;
    long long q = 53;

    // Calculate n
    long long n = p * q;

    // Euler's totient
    long long phi = (p - 1) * (q - 1);

    // Choose public exponent e
    long long e = 17;

    // Make sure e and phi are coprime
    if (gcd(e, phi) != 1) {
        cout << "Invalid e\n";
        return 1;
    }

    // Calculate private exponent d
    long long d = modInverse(e, phi);

    cout << "Public Key  = (" << e << ", " << n << ")\n";
    cout << "Private Key = (" << d << ", " << n << ")\n";

    // Message
    long long message = 65;

    cout << "\nOriginal message: " << message << endl;

    // --------------------------------------------------
    // Encryption
    //
    // C = M^e mod n
    // --------------------------------------------------
    long long ciphertext = modPow(message, e, n);

    cout << "Encrypted: " << ciphertext << endl;

    // --------------------------------------------------
    // Decryption
    //
    // M = C^d mod n
    // --------------------------------------------------
    long long decrypted = modPow(ciphertext, d, n);

    cout << "Decrypted: " << decrypted << endl;

    return 0;
}