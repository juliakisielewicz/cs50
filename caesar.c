#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

string encrypt(string plain, int key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./ceasar key\n");
        return 1;
    }
    
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if(! isdigit(argv[1][i]))
        {
            printf("Usage: ./ceasar key\n");
            return 1;
        }
    }
    
    int k = atoi(argv[1]);

    string plaintext = get_string("plaintext: ");
    
    string ciphertext = encrypt(plaintext, k);
    
    //Display result
    printf("ciphertext: %s\n", ciphertext);
    
    return 0;
}
    
    
string encrypt(string plain, int key)
{
    string cipher = plain;
    
    for (int i = 0; i < strlen(plain); i++)
    {
        if (islower(plain[i]))
        {
            cipher[i] = (plain[i] + key - 97) % 26 + 97;
        }
        else if (isupper(plain[i]))
        {
            cipher[i] = (plain[i] + key - 65) % 26 + 65;
        }
        else 
        {
            cipher[i] = plain[i];
        }
    }
    
    return cipher;
}
