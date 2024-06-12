#include <stdio.h>
int main(void)
{
    char text[100];
    int shift;
    printf("Enter a string to encrypt: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter shift value (1-25): ");
    scanf("%d", &shift);
    for(int i = 0; text[i] != '\0'; ++i)
    {
        char ch = text[i];
        if(ch >= 'A' && ch <= 'Z')
        {
            ch = ch + shift;
            if(ch > 'Z')
            {
                ch = ch - 26;
            }
            text[i] = ch;
        }
        else if(ch >= 'a' && ch <= 'z')
        {
            ch = ch + shift;
            if(ch > 'z')
            {
                ch = ch - 26;
            }
            text[i] = ch;
        }
    }
    printf("Encrypted string: %s\n", text);
    return 0;
}
