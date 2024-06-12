#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt a single character using the Vigenère table
char encryptChar(char plaintextChar, char keyChar) {
    if (!isalpha(plaintextChar)) {
        return plaintextChar;
    }
    
    char base = isupper(plaintextChar) ? 'A' : 'a';
    char baseKey = isupper(keyChar) ? 'A' : 'a';
    return (plaintextChar - base + (keyChar - baseKey)) % 26 + base;
}

// Function to encrypt the entire plaintext using the Vigenère cipher
void vigenereEncrypt(char plaintext[], char key[], char ciphertext[]) {
    long plaintextLen = strlen(plaintext);
    long keyLen = strlen(key);
    
    for (int i = 0, j = 0; i < plaintextLen; i++) {
        char currentKeyChar = toupper(key[j % keyLen]);
        ciphertext[i] = encryptChar(plaintext[i], currentKeyChar);
        if (isalpha(plaintext[i])) {
            j++;
        }
    }
    ciphertext[plaintextLen] = '\0';
}

int main(void) {
    char plaintext[256];
    char key[256];
    char ciphertext[256];

    // Input the plaintext and key
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    // Remove the newline character from the end of the plaintext
    plaintext[strcspn(plaintext, "\n")] = '\0';

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    // Remove the newline character from the end of the key
    key[strcspn(key, "\n")] = '\0';

    vigenereEncrypt(plaintext, key, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

