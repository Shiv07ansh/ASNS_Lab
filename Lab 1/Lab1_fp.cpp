#include <iostream>
#include <string>
#include <cctype>

using namespace std;

struct Position {
    int row;
    int col;
};

class PF {
private:
    char grid[5][5];

public:

    // Generate the 5x5 Playfair grid
    void generateGrid(string key) {

        string sequence;
        bool used[26] = {false};

        // Playfair combines I and J
        used['J' - 'A'] = true;

        // Add characters from the key
        for (char c : key) {

            c = toupper(c);

            if (c == 'J')
                c = 'I';

            if (c >= 'A' && c <= 'Z' && !used[c - 'A']) {
                sequence += c;
                used[c - 'A'] = true;
            }
        }

        // Add remaining alphabet
        for (char c = 'A'; c <= 'Z'; c++) {

            if (c == 'J')
                continue;

            if (!used[c - 'A']) {
                sequence += c;
                used[c - 'A'] = true;
            }
        }

        // Fill the grid
        int index = 0;

        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 5; col++) {

                grid[row][col] = sequence[index];
                index++;
            }
        }
    }


    // Print the grid
    void printGrid() {

        for (int row = 0; row < 5; row++) {

            for (int col = 0; col < 5; col++) {
                cout << grid[row][col] << ' ';
            }

            cout << '\n';
        }
    }


    // Find the position of a character
    Position getGridPosition(char c) {

        c = toupper(c);

        if (c == 'J')
            c = 'I';

        for (int row = 0; row < 5; row++) {

            for (int col = 0; col < 5; col++) {

                if (grid[row][col] == c)
                    return {row, col};
            }
        }
    }


    // Determine which Playfair case applies
    int compare(char a, char b) {

        Position pos_a = getGridPosition(a);
        Position pos_b = getGridPosition(b);

        // Same row
        if (pos_a.row == pos_b.row)
            return 1;

        // Same column
        if (pos_a.col == pos_b.col)
            return 2;

        // Rectangle
        return 3;
    }


    // Encrypt plaintext
    string encrypt(string plaintext) {

        string prepared;

        // Convert to uppercase and remove non-letters
        for (char c : plaintext) {

            c = toupper(c);

            if (c >= 'A' && c <= 'Z') {

                if (c == 'J')
                    c = 'I';

                prepared += c;
            }
        }


        // Prepare plaintext into pairs
        string pairs;

        for (int i = 0; i < prepared.length(); i++) {

            char a = prepared[i];

            // If this is the last character
            if (i + 1 == prepared.length()) {
                pairs += a;
                pairs += 'X';
                break;
            }

            char b = prepared[i + 1];

            // Same letters cannot form a pair
            if (a == b) {
                pairs += a;
                pairs += 'X';
            }
            else {
                pairs += a;
                pairs += b;
                i++;
            }
        }


        // Encrypt each pair
        string ciphertext;

        for (int i = 0; i < pairs.length(); i += 2) {

            char a = pairs[i];
            char b = pairs[i + 1];

            Position pos_a = getGridPosition(a);
            Position pos_b = getGridPosition(b);

            int case_ = compare(a, b);


            // CASE 1: Same row
            if (case_ == 1) {

                pos_a.col = (pos_a.col + 1) % 5;
                pos_b.col = (pos_b.col + 1) % 5;
            }


            // CASE 2: Same column
            else if (case_ == 2) {

                pos_a.row = (pos_a.row + 1) % 5;
                pos_b.row = (pos_b.row + 1) % 5;
            }


            // CASE 3: Rectangle
            else {

                int temp = pos_a.col;
                pos_a.col = pos_b.col;
                pos_b.col = temp;
            }


            ciphertext += grid[pos_a.row][pos_a.col];
            ciphertext += grid[pos_b.row][pos_b.col];
        }

        return ciphertext;
    }
};


int main() {

    PF cipher;

    string key;
    string plaintext;

    cout << "Enter key: ";
    cin >> key;

    cin.ignore();

    cout << "Enter plaintext: ";
    getline(cin, plaintext);


    cipher.generateGrid(key);

    cout << "\nPlayfair Grid:\n";
    cipher.printGrid();


    string ciphertext = cipher.encrypt(plaintext);

    cout << "\nCiphertext: " << ciphertext << '\n';

    return 0;
}