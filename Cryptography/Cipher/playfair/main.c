#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Function to preprocess the key
void preprocessKey(char key[], char cleanedKey[]) {
    int cleanedIndex = 0;
    int alpha[26] = {0}; // To track used characters

    for (int i = 0; key[i] != '\0'; i++) {
        char letter = toupper(key[i]);
        if (letter == 'J') {
            letter = 'I'; // Treat 'J' as 'I'
        }
        if (isalpha(letter) && !alpha[letter - 'A']) {
            cleanedKey[cleanedIndex++] = letter;
            alpha[letter - 'A'] = 1;
        }
    }
    cleanedKey[cleanedIndex] = '\0';
}

// Function to fill the Playfair matrix with the cleaned key
void fillMatrix(char matrix[][SIZE], char cleanedKey[]) {
    int alpha[26] = {0}; // To track used characters
    long keyLen = strlen(cleanedKey);
    int index = 0;

    for (int i = 0; i < keyLen; i++) {
        matrix[index / SIZE][index % SIZE] = cleanedKey[i];
        alpha[cleanedKey[i] - 'A'] = 1;
        index++;
    }

    for (char letter = 'A'; letter <= 'Z'; letter++) {
        if (letter == 'J') continue; // Skip 'J'
        if (!alpha[letter - 'A']) {
            matrix[index / SIZE][index % SIZE] = letter;
            index++;
        }
    }
}

// Function to find the position of a letter in the matrix
void findPosition(char matrix[][SIZE], char letter, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt a pair of letters using the Playfair matrix
void encryptPair(char matrix[][SIZE], char a, char b, char *encrypted) {
    int rowA, colA, rowB, colB;
    findPosition(matrix, a, &rowA, &colA);
    findPosition(matrix, b, &rowB, &colB);

    if (rowA == rowB) { // Same row
        encrypted[0] = matrix[rowA][(colA + 1) % SIZE];
        encrypted[1] = matrix[rowB][(colB + 1) % SIZE];
    } else if (colA == colB) { // Same column
        encrypted[0] = matrix[(rowA + 1) % SIZE][colA];
        encrypted[1] = matrix[(rowB + 1) % SIZE][colB];
    } else { // Form a rectangle
        encrypted[0] = matrix[rowA][colB];
        encrypted[1] = matrix[rowB][colA];
    }
}

// Function to format the plaintext for Playfair encryption
void formatPlaintext(char plaintext[], char formatted[]) {
    long len = strlen(plaintext);
    int index = 0;

    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            char letter = toupper(plaintext[i]);
            if (letter == 'J') letter = 'I'; // Treat 'J' as 'I'
            formatted[index++] = letter;
        }
    }

    if (index % 2 != 0) {
        formatted[index++] = 'X'; // Add padding if necessary
    }
    formatted[index] = '\0';
}

// Function to encrypt the formatted plaintext using the Playfair cipher
void playfairEncrypt(char matrix[][SIZE], char plaintext[], char ciphertext[]) {
    long len = strlen(plaintext);
    for (int i = 0; i < len; i += 2) {
        char a = plaintext[i];
        char b = (i + 1 < len) ? plaintext[i + 1] : 'X'; // Padding if odd length
        encryptPair(matrix, a, b, &ciphertext[i]);
    }
    ciphertext[len] = '\0';
}

int main(void) {
    char key[100];
    char cleanedKey[26];
    char matrix[SIZE][SIZE];
    char plaintext[1000];
    char formatted[1000];
    char ciphertext[1000];

    // Input the keyword and plaintext
    printf("Enter the keyword (no spaces): ");
    scanf("%s", key);
    printf("Enter the plaintext: ");
    scanf("%s", plaintext);

    preprocessKey(key, cleanedKey);
    fillMatrix(matrix, cleanedKey);
    formatPlaintext(plaintext, formatted);
    playfairEncrypt(matrix, formatted, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
