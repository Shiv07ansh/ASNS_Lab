#include <iostream>
#include <numeric>
#include <string>

using namespace std;




int main(){

	string text;
	string k;
	int key[2][2];
	
	cout << " Enter plaintext: ";
	cin >> text;
	
	char a, b, c, d;
    cout << "Enter key:\n";
	cin >> k;
	
	
	key[0][0] = k[0] - 'A';
	key[0][1] = k[1] - 'A';
	key[1][0] = k[2] - 'A';
	key[1][1] = k[3] - 'A';

	
	//Adding bogus 'X' if odd
	if( text.length()%2 != 0)
		text += 'X';
	
	string encrypt = "";
	for (int i=0; i < text.length(); i+=2){
	//assuming m=2
	int a = text[i] - 'A';
	int b = text[i+1] - 'A';
	
	int x = (key[0][0] * a + key[0][1] * b);
	int y = (key[1][0] * a + key[1][1] * b);
	
	x = x%26;
	y = y%26;
	
	
	encrypt += char(x + 'A');
	encrypt += char(y + 'A');
	}
	cout << "Ciphertext is: " << encrypt;
	
	// Find determinant
    int det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
	
	//make determinant positive and within 26
    det = (det % 26 + 26) % 26;
	
	//Find M.I. of Det
	int detInv = -1;
	
	for(int i=0; i <26; i++){
	if((det*i)%26==1){
		detInv = i;
		break; 		}
	}
	
	if (detInv == -1)
	{
		cout << " No inverse for this key ";
		return 0;
	}
	
	
	    // Inverse key matrix
    int invKey[2][2];

    invKey[0][0] = (key[1][1] * detInv) % 26;
    invKey[0][1] = (-key[0][1] * detInv % 26 + 26) % 26;
    invKey[1][0] = (-key[1][0] * detInv % 26 + 26) % 26;
    invKey[1][1] = (key[0][0] * detInv) % 26;
	
	cout << " The decipher key is: " << invKey;
	
	// Decryption
    string decrypt = "";

    for (int i = 0; i < encrypt.length(); i += 2) {
        int a = encrypt[i] - 'A';
        int b = encrypt[i + 1] - 'A';
		
		int x = (invKey[0][0] * a + invKey[0][1] * b) % 26;
        int y = (invKey[1][0] * a + invKey[1][1] * b) % 26;
		
		
		decrypt += char(x + 'A');
        decrypt += char(y + 'A');
	
}

	cout << "Decrypted text: " << decrypt << endl;

    return 0;
	
}

