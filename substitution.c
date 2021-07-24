#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

string encrypt(string plain, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (! isalpha(argv[1][i]))
        {
            printf("Key must contain 26 alphabetic characters.\n");
            return 1;
        }
    }
    //ONLY UNIQUE
    int size = 26;
    int occurences[26] = {0};
    
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (islower(argv[1][i]))
        {
            occurences[argv[1][i] - 97]++;
        }
        else if (isupper(argv[1][i]))
        {
            occurences[argv[1][i] - 65]++;
        }
    }
    
    bool unique = true;
    
    for (int i = 0; i < size; i++)
    {
        if(occurences[i] != 1)
        {
            unique = false;
        }
    }
        
        if(! unique)
        {
            printf("Key must contain 26 unique characters.\n");
            return 1;
        }
    
    
    string plaintext = get_string("plaintext: ");
    
    string ciphertext = encrypt(plaintext, argv[1]);
    
    //Display result
    printf("ciphertext: %s\n", ciphertext);
    
    return 0;
    
}

string encrypt(string plain, string key)
{
    string cipher = plain;
    
    for (int i = 0; i < strlen(plain); i++)
    {
        if (islower(plain[i]))
        {
            cipher[i] = tolower(key[plain[i] - 97]);
        }
        else if (isupper(plain[i]))
        {
            cipher[i] = toupper(key[plain[i] - 65]);
        }
        else 
        {
            cipher[i] = plain[i];
        }
    }
    
    return cipher;
}
