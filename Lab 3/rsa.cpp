#include <iostream>
#include <numeric>
using namespace std;


class RSA{

public:     
	long long p, q; // primes
    long long n, phi; // product, totient
    long long e, d; //exponenets
	
	
//find GCD
	long long gcd(long long a, long long b){
			while (b != 0)
			{
				long long temp = b;
				b = a % b;
				a = temp;
			}
			return a;
	}
	
// get totient
		long long findTotient() {
        return (p - 1) * (q - 1);
    }
	
// public and private key

	long long findPublicKey(){
		for (long long i = 2; i < phi; i++){
			if(gcd(i, phi) == 1)
				return i;
		}
		return -1;
	}
	
	long long findPrivateKey(){
		long long i = 1;

        while ((i * e) % phi != 1)
            i++;

        return i;
	}
	
//exponent
	long long power(long long base, long long exponent)
    {
        long long result = 1;

        for (long long i = 0; i < exponent; i++)
            result = (result * base) % n;

        return result;
    }

//rsa

    RSA(long long prime1, long long prime2)
    {
        p = prime1;
        q = prime2;

        n = p * q;
        phi = findTotient();

        e = findPublicKey();
        d = findPrivateKey();
    }
	
	long long encrypt(long long message)
    {
        return power(message, e);
    }

    long long decrypt(long long ciphertext)
    {
        return power(ciphertext, d);
    }

    long long getE()
    {
        return e;
    }

    long long getD()
    {
        return d;
    }

    long long getN()
    {
        return n;
    }


};

long long main() {

	long long message;
	cout << "Enter plalong longext\n";
	cin >> message;
	
    long long p, q;

    cout << "Enter p: ";
    cin >> p;

    cout << "Enter q: ";
    cin >> q;

    RSA rsa(p, q);
	
	long long encrypted = rsa.encrypt(message);
    long long decrypted = rsa.decrypt(encrypted);
	
	cout << " Totient : (" << rsa.findTotient() << ")"  << endl;
    cout << "Public Key  : (" << rsa.getE() << ", " << rsa.getN() << ")" << endl;
    cout << "Private Key : (" << rsa.getD() << ", " << rsa.getN() << ")" << endl;

    cout << "Encrypted   : " << encrypted << endl;
    cout << "Decrypted   : " << decrypted << endl;

    return 0;
	
}
