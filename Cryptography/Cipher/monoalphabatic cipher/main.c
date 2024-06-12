#include<stdio.h>
#include <string.h>
#include <ctype.h>
void en(char plaintext[], char key[], char ciphertext[]);

void en(char plaintext[],char key[],char ciphertext[]){
    int i;
    for(i=0;plaintext[i]!='\0';i++){
        if(isalpha(plaintext[i])){
            char letter = toupper(plaintext[i]);
            int position=letter-'A';
            ciphertext[i]=key[position];
        }
        else{
            ciphertext[i]=plaintext[i];

        }
    }

       ciphertext[i] = '\0';

}
int main(void){
    char plaintext[256] ;
    printf("Enter the plan text to perform encryption ");
    fgets(plaintext,sizeof(plaintext),stdin);
    char key[27] = "QWERTYUIOPASDFGHJKLZXCVBNM"; 
    char ciphertext[256];
   en(plaintext,key,ciphertext);
    printf("Cipher text %s\n",ciphertext);
    return 0;
    
}
